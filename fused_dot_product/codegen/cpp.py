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


class _CppEmitter:
    def __init__(self, jittable: bool = True) -> None:
        self.jittable = jittable
        self._reserved_names = {}
        self._function_cache: dict[_Fingerprint, str] = {}
        self._functions: list[str] = []
        self._fingerprint_cache: dict[Node, _Fingerprint] = {}

    def emit_cpp(self, root: Node, function_name: str) -> str:
        if isinstance(root.node_type, TupleT):
            raise CppLoweringError("Tuple-typed entry points are not supported in C++ lowering")
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
        includes = ["#include <cstdint>"]
        if self.jittable:
            includes.append("#include <array>")
        else:
            includes.extend([
                "#include <tuple>",
                "#include <ac_int.h>",
            ])
        parts = [
            "#pragma once",
            *includes,
            "",
            "template <int W>",
            "using ac_uint = ac_int<W, false>;",
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
        signature = f"static inline {self._render_type(return_type)} {name}({params_sig})"
        
        body = [*ctx.statements, f"return {result.expr};"]
        indented_body = "\n".join(f"    {line}" for line in body)
        return "\n".join([signature + f" {{  // {original_name}", indented_body, "}"])
    
    def _collect_vars(self, root: Node) -> list[Var]:
        return root.inner_args

    def _should_inline(self, node: Node) -> bool:
        return isinstance(node, (primitive, composite)) and (
            bool(getattr(node, "c_inline", False))
            or isinstance(node.node_type, TupleT)  # FOR NOW. SOME TROUBLES WIT JIT AND ARRAYS - JUST INLINE EVERY TUPLE
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
            if self._should_inline(node):  # Inlining functions into current call
                # Lowering args
                lowered_args = [self._lower(arg, env, ctx) for arg in node.args]
                inline_env = dict(env)
                inline_env.update(dict(zip(node.inner_args, lowered_args)))

                # Lowering body
                if not node.c_inline:
                    ctx.statements.append(f"// begin inline {type(node).__name__} {node.name}")
                lowered = self._lower(node.inner_tree, inline_env, ctx)
                if not node.c_inline:
                    ctx.statements.append(f"// end inline {type(node).__name__} {node.name}")
                    
                ctx.memo[node] = lowered
                return lowered
            else:  # Create a separate function for the node
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

    # Caching for not lowering the same function twice
    def _fingerprint(self, node: Node) -> _Fingerprint:
        if node in self._fingerprint_cache:
            return self._fingerprint_cache[node]
        
        if isinstance(node, Var):
            result = ("Var", node.name, repr(node.node_type))
        elif isinstance(node, Const):
            result = ("Const", self._value_key(node.val))
        elif isinstance(node, Op):
            lowering_fingerprint = node.c_lowering(
                [f"${idx}" for idx in range(len(node.args))],
                self.jittable,
            )
            result = (
                "Op",
                node.name,
                repr(node.node_type),
                lowering_fingerprint,
                tuple(self._fingerprint(arg) for arg in node.args),
            )
        elif isinstance(node, (primitive, composite)):
            result = (
                type(node).__name__,
                node.name,
                repr(node.node_type),
                tuple(repr(arg.node_type) for arg in node.inner_args),
                self._fingerprint(node.inner_tree),
            )
        else:
            raise CppLoweringError(f"Unsupported node type: {type(node).__name__}")

        self._fingerprint_cache[node] = result
        return result

    def _value_key(self, value: RuntimeType) -> tp.Any:
        if isinstance(value, Tuple):
            return (
                type(value).__name__,
                tuple(self._value_key(arg) for arg in value.args),
            )
        return (type(value).__name__, tuple(sorted(vars(value).items())))
    
    def _lower_const(self, value: RuntimeType) -> _CppValue:
        cpp_type = self._render_type(value.static_type())
        return _CppValue(expr=self._const_expr(value), cpp_type=cpp_type)

    def _const_expr(self, value: RuntimeType) -> str:
        if isinstance(value, Tuple):
            for arg in value.args:
                if isinstance(arg, Tuple):
                    raise CppLoweringError("Nested tuples are not supported in C++ lowering")
            args = [self._lower_const(arg) for arg in value.args]
            if self.jittable:
                return (
                    f"{self._render_type(value.static_type())}{{"
                    + ", ".join(f"static_cast<uint64_t>({arg.expr})" for arg in args)
                    + "}"
                )
            return f"std::make_tuple({', '.join(arg.expr for arg in args)})"
        else:
            return self._cast(value.static_type(), str(value.val))
    
    def _lower_op(
        self,
        node: Op,
        env: dict[Node, _CppValue],
        ctx: _FunctionContext,
    ) -> _CppValue:
        if node.c_lowering is None:
            raise CppLoweringError(f"Unsupported op lowering for {node.name}")
        
        lowered_args = [self._lower(arg, env, ctx).expr for arg in node.args]
        expr = self._cast(node.node_type, node.c_lowering(lowered_args, self.jittable))
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
        call_args = ", ".join(self._render_public_arg(arg) for arg in args)
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
        return type_.to_cpp_type(jittable=self.jittable)
    
    def _cast(self, type_: StaticType, expr: str) -> str:
        if isinstance(type_, TupleT):
            return expr
        if self.jittable:
            return f"{self._render_type(type_)}({self._mask(expr, type_)})"
        return f"{self._render_type(type_)}({expr})"

    def _mask(self, expr: str, type_):
        return f"({expr}) & {self._mask_literal(type_.total_bits())}"

    def _mask_literal(self, bits: int) -> str:
        return str((1 << bits) - 1)

    def _render_public_arg(self, arg: Var) -> str:
        if not self.jittable:
            return arg.name
        return f"({arg.name} & {self._mask_literal(arg.node_type.total_bits())})"
    
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


def lower_to_cpp(
    root: Node,
    function_name: str | None = None,
    jittable: bool = True,
) -> str:
    if function_name is None:
        function_name = root.name
    emitter = _CppEmitter(jittable=jittable)
    return emitter.emit_cpp(root=root, function_name=function_name)
