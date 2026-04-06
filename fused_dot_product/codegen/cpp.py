from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass, field
import typing as tp

from ..ast.node import Node
from ..ast.nodes import Const, Op, Var, composite, primitive
from ..types.runtime import BFloat16, Bool, Float32, Q, RuntimeType, Tuple, UQ
from ..types.static import StaticType, TupleT


class CppLoweringError(RuntimeError):
    pass


@dataclass(frozen=True)
class _CppValue:
    expr: str
    cpp_type: str


# Helper object for lowering one function at a time
@dataclass
class _FunctionContext:
    memo: dict[Node, _CppValue] = field(default_factory=dict)
    statements: list[str] = field(default_factory=list)


_Fingerprint = tuple[tp.Any, ...]


# TODO: would be nice to support nested arrays
class _CppEmitter:
    def __init__(self, jitable: bool = True) -> None:
        self._reserved_names = {}
        self._function_cache: dict[_Fingerprint, str] = {}
        self._functions: list[str] = []
        self._fingerprint_cache: dict[Node, _Fingerprint] = {}
        self._jitable = jitable

    def emit_cpp(self, root: Node, function_name: str) -> str:
        if self._jitable is True:
            public_name = self._make_name(function_name)
            internal_name = self._make_name(f"{public_name}_impl")
            self.emit_function(root=root, function_name=internal_name)
            self._functions.append(
                self._render_public_wrapper(
                    public_name=public_name,
                    internal_name=internal_name,
                    args=root.inner_args,
                    return_type=root.node_type,
                )
            )
            parts = [
                "#pragma once",
                "#include <array>",
                "#include <cstdint>",
                "",
                *list(self._functions),
            ]
        else: 
            self.emit_function(root=root, function_name=function_name)
            parts = [
                "#include <array>",
                "#include <ap_int.h>",
                "#include <cstdint>",
                "",
                *list(self._functions),
            ]
        return "\n".join(parts)

    def emit_function(self, root: Node, function_name: str) -> str:
        assert isinstance(root, (composite, primitive)), "Can lower only Primitive/Composite"

        cache_key = self._fingerprint(root)
        if cache_key in self._function_cache:
            return self._function_cache[cache_key]
        self._function_cache[cache_key] = function_name
        
        args = self._collect_vars(root)
        env = {
            arg: _CppValue(expr=arg.name, cpp_type=self._render_type(arg.node_type))
            for arg in root.inner_args
        }
        
        rendered = self._render_function(
            name=function_name,
            args=root.inner_args,
            return_type=root.node_type,
            env=env,
            body_root=root.inner_tree,
            original_name=root.name,
        )
        self._functions.append(rendered)
        return function_name
    
    def _render_function(
        self,
        name: str,
        args: list[Var],
        return_type: StaticType,
        env: dict[Node, _CppValue],
        body_root: Node,
        original_name: str,
    ) -> str:
        ctx = _FunctionContext()
        result = self._lower(body_root, env, ctx)
        
        params_sig = ", ".join(
            f"{self._render_type(arg.node_type)} {arg.name}" for arg in args
        )
        if self._jitable:
            signature = f"static inline {self._render_type(return_type)} {name}({params_sig})"
        else:
            signature = f"{self._render_type(return_type)} {name}({params_sig})"
        
        body = [*ctx.statements, f"return {result.expr};"]
        indented_body = "\n".join(f"    {line}" for line in body)
        return "\n".join([signature + f" {{  // {original_name}", indented_body, "}"])
    
    def _collect_vars(self, root: Node) -> list[Var]:
        return root.inner_args

    def _should_inline(self, node: Node) -> bool:
        return isinstance(node, (primitive, composite)) and bool(
            getattr(node, "c_inline", False)
        )

    def _lower(
        self,
        node: Node,
        env: dict[Node, _CppValue],
        ctx: _FunctionContext,
    ) -> _CppValue:
        if isinstance(node, Var):
            try:
                return env[node]
            except KeyError as exc:
                raise CppLoweringError(
                    f"Unbound variable during lowering: {node.name}"
                ) from exc

        if node in ctx.memo:
            return ctx.memo[node]

        if isinstance(node, Const):
            lowered = self._lower_const(node.val)
            ctx.memo[node] = lowered
            return lowered

        if isinstance(node, Op):
            lowered = self._lower_op(node, env, ctx)
            ctx.memo[node] = lowered
            return lowered

        if isinstance(node, (primitive, composite)):
            if self._should_inline(node):
                lowered_args = [self._lower(arg, env, ctx) for arg in node.args]
                inline_env = dict(env)
                inline_env.update(dict(zip(node.inner_args, lowered_args)))
                lowered = self._lower(node.inner_tree, inline_env, ctx)
                ctx.memo[node] = lowered
                return lowered
            else:
                lowered_args = [self._lower(arg, env, ctx) for arg in node.args]
                helper_name = self._function_cache.get(self._fingerprint(node))
                if helper_name is None:
                    helper_name = self._make_name(node.name)
                    self.emit_function(
                        root=node,
                        function_name=helper_name,
                    )
                expr = f"{helper_name}({', '.join(arg.expr for arg in lowered_args)})"
                lowered = self._emit_temp(node.node_type, expr, node.name, ctx)
                ctx.memo[node] = lowered
                return lowered

        raise CppLoweringError(f"Unsupported node type: {type(node).__name__}")

    def _fingerprint(self, node: Node) -> _Fingerprint:
        if node in self._fingerprint_cache:
            return self._fingerprint_cache[node]
        if isinstance(node, Var):
            result = ("Var", node.name, node.node_type.to_cpp_type(jitable=self._jitable))
        elif isinstance(node, Const):
            result = ("Const", node.name, node.node_type.to_cpp_type(jitable=self._jitable))
        elif isinstance(node, Op):
            template = None
            result = (
                "Op",
                node.name,
                node.node_type.to_cpp_type(jitable=self._jitable),
                tuple(self._fingerprint(arg) for arg in node.args),
            )
        elif isinstance(node, (primitive, composite)):
            result = (
                type(node).__name__,
                node.name,
                node.node_type.to_cpp_type(jitable=self._jitable),
                tuple(arg.node_type.to_cpp_type(jitable=self._jitable) for arg in node.inner_args),
                self._fingerprint(node.inner_tree),
            )
        else:
            raise CppLoweringError(f"Unsupported node type: {type(node).__name__}")

        result = self._freeze(result)
        self._fingerprint_cache[node] = result
        return result
    
    def _freeze(self, value: tp.Any) -> tp.Any:
        if isinstance(value, StaticType):
            return value.to_cpp_type(jitable=self._jitable)
        if isinstance(value, RuntimeType):
            return self._fingerprint_value(value)
        if isinstance(value, list):
            return tuple(self._freeze(item) for item in value)
        if isinstance(value, tuple):
            return tuple(self._freeze(item) for item in value)
        if isinstance(value, dict):
            return tuple(sorted((key, self._freeze(item)) for key, item in value.items()))
        return value
    
    
    def _lower_const(self, value: RuntimeType) -> _CppValue:
        cpp_type = self._render_type(value.static_type())
        return _CppValue(expr=self._const_expr(value), cpp_type=cpp_type)

    def _const_expr(self, value: RuntimeType) -> str:
        if isinstance(value, Tuple):
            for arg in value.args:
                if isinstance(arg, Tuple):
                    raise CppLoweringError("Nested tuples are not supported in C++ lowering")
            args = [self._lower_const(arg) for arg in value.args]
            return (
                f"{self._render_type(value.static_type())}{{"
                + ", ".join(f"static_cast<uint64_t>({arg.expr})" for arg in args)
                + "}"
            )

        if isinstance(value, Bool):
            return self._cast(value.static_type(), str(value.val))

        if isinstance(value, (Q, UQ, Float32, BFloat16)):
            return self._cast(value.static_type(), str(value.val))

        raise CppLoweringError(f"Unsupported constant type: {type(value).__name__}")

    def _lower_op(
        self,
        node: Op,
        env: dict[Node, _CppValue],
        ctx: _FunctionContext,
    ) -> _CppValue:
        if node.c_lowering is None:
            raise CppLoweringError(f"Unsupported op lowering for {node.name}")
        
        lowered_args = [self._lower(arg, env, ctx).expr for arg in node.args]
        expr = self._cast(node.node_type, node.c_lowering(lowered_args))
        return self._emit_temp(node.node_type, expr, node.name, ctx)
    
    def _signature(self, name: str, args: list[Var], return_type: StaticType) -> str:
        params_sig = ", ".join(
            f"{self._render_type(arg.node_type)} {arg.name}" for arg in args
        )
        return f"{self._render_type(return_type)} {name}({params_sig})"

    def _render_public_wrapper(
        self,
        public_name: str,
        internal_name: str,
        args: list[Var],
        return_type: StaticType,
    ) -> str:
        call_args = ", ".join(arg.name for arg in args)
        if isinstance(return_type, TupleT):
            params = [f"{self._render_type(arg.node_type)} {arg.name}" for arg in args]
            params.append("uint64_t* out")
            body = [
                f'extern "C" inline void {public_name}({", ".join(params)}) {{',
                f"    const {self._render_type(return_type)} result = {internal_name}({call_args});",
            ]
            body.extend(
                f"    out[{idx}] = result[{idx}];" for idx in range(len(return_type.args))
            )
            body.append("}")
            return "\n".join(body)

        wrapper_signature = self._signature(
            name=public_name,
            args=args,
            return_type=return_type,
        )
        return "\n".join(
            [
                f'extern "C" inline {wrapper_signature} {{',
                f"    return {internal_name}({call_args});",
                "}",
            ]
        )
    
    def _render_type(self, type_: StaticType) -> str:
        if isinstance(type_, TupleT) and any(isinstance(arg, TupleT) for arg in type_.args):
            raise CppLoweringError("Nested tuples are not supported in C++ lowering")
        return type_.to_cpp_type(jitable=self._jitable)
    
    def _cast(self, type_: StaticType, expr: str) -> str:
        if isinstance(type_, TupleT):
            return expr
        return f"{self._render_type(type_)}({expr})"
    
    def _emit_temp(
        self,
        type_: StaticType,
        expr: str,
        name: str,
        ctx: _FunctionContext,
    ) -> _CppValue:
        temp_name = self._make_name("tmp")
        cpp_type = self._render_type(type_)
        ctx.statements.append(f"const {cpp_type} {temp_name} = {expr};  // {name}")
        return _CppValue(expr=temp_name, cpp_type=cpp_type)
    
    def _make_name(self, base: str) -> str:
        safe_base = self._sanitize_identifier(base)
        name = safe_base
        i = 0
        while True:
            i += 1
            if name in self._reserved_names:
                name = f"{safe_base}_{i}"
            else:
                self._reserved_names[name] = True
                break
        return name
    
    def _sanitize_identifier(self, name: str) -> str:
        chars = [ch if ch.isalnum() or ch == "_" else "_" for ch in name]
        safe = "".join(chars).strip("_") or "tmp"
        if safe[0].isdigit():
            safe = f"_{safe}"
        return safe


def lower_to_cpp(root: Node, jitable: bool = True, function_name: str | None = None) -> str:
    if function_name is None:
        function_name = root.name
    emitter = _CppEmitter(jitable=jitable)
    return emitter.emit_cpp(root=root, function_name=function_name)
