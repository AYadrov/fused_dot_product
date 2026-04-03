from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass
import typing as tp

from ..ast.node import Node
from ..ast.nodes import Const, Op, Var, composite, primitive
from ..types.runtime import BFloat16, Bool, Float32, Q, RuntimeType, Tuple, UQ
from ..types.static import StaticType, TupleT, UQT


class CppLoweringError(RuntimeError):
    pass


@dataclass(frozen=True)
class _CppValue:
    expr: str
    cpp_type: str


class _CppEmitter:
    def __init__(self) -> None:
        self.sym_counter = 0
        self._memo: dict[Node, _CppValue] = {}
        self._statements: list[str] = []
        self._temp_index = 0

    def make_name(base: str):
        name = base + f"_{self.sym_counter}"
        self.sym_counter += 1
        return name
        
    def emit_function(self, root: Node) -> str:
        function_name = root.name
        args = self._collect_vars(root)
        
        env = {
            node: _CppValue(expr=node.name, cpp_type=self._render_type(node.node_type))
            for node in args
        }
        result = self._lower(root, env)
        
        params_sig = ", ".join(
            f"{self._render_type(node.node_type)} {node.name}" for node in params
        )
        signature = f"{self._render_type(root.node_type)} {function_name}({params_sig})"
        body: list[str] = []
        body.extend(self._statements)
        body.append(f"return {result.expr};")
        indented_body = "\n".join(f"    {line}" for line in body)
        
        return "\n".join(
            [
                "#include <ap_int.h>",
                "#include <tuple>",
                "",
                signature + " {",
                indented_body,
                "}",
            ]
        )
    
    def _collect_vars(self, root: Node) -> list[Var]:
        variables = []
        for arg in root.args:
            if isinstance(arg, Var):
                variables.append(arg)
        return variables
    
    def _lower(self, node: Node, env: dict[Node, _CppValue]) -> _CppValue:
        if isinstance(node, Var):
            try:
                return env[node]
            except KeyError as exc:
                raise CppLoweringError(f"Unbound variable during lowering: {node.name}") from exc
        
        if node in self._memo:
            return self._memo[node]
        
        if isinstance(node, Const):
            lowered = self._lower_const(node.val)
            self._memo[node] = lowered
            return lowered
        
        if isinstance(node, Op):
            lowered = self._lower_op(node, env)
            self._memo[node] = lowered
            return lowered
        
        if isinstance(node, (primitive, composite)):
            local_env = dict(env)
            lowered_args = [self._lower(arg, env) for arg in node.args]
            for inner_arg, lowered_arg in zip(node.inner_args, lowered_args):
                local_env[inner_arg] = lowered_arg
            lowered = self._lower(node.inner_tree, local_env)
            self._memo[node] = lowered
            return lowered
        
        raise CppLoweringError(f"Unsupported node type: {type(node).__name__}")

    def _lower_const(self, value: RuntimeType) -> _CppValue:
        if isinstance(value, Tuple):
            args = [self._lower_const(arg) for arg in value.args]
            cpp_type = self._render_type(value.static_type())
            expr = f"std::make_tuple({', '.join(arg.expr for arg in args)})"
            return _CppValue(expr=expr, cpp_type=cpp_type)

        cpp_type = self._render_type(value.static_type())
        return _CppValue(expr=self._const_expr(value), cpp_type=cpp_type)

    def _const_expr(self, value: RuntimeType) -> str:
        if isinstance(value, Bool):
            return self._cast(value.static_type(), str(value.val))
        if isinstance(value, (Q, UQ, Float32, BFloat16)):
            return self._cast(value.static_type(), str(value.val))
        raise CppLoweringError(f"Unsupported constant type: {type(value).__name__}")

    def _lower_op(self, node: Op, env: dict[Node, _CppValue]) -> _CppValue:
        if node.c_lowering is not None:
            lowered_args = [self._lower(arg, env).expr for arg in node.args]
            expr = self._cast(node.node_type, node.c_lowering(lowered_args))
            return self._emit_temp(node.node_type, expr, node.name)

        name = node.name
        raise CppLoweringError(f"Unsupported op lowering for {name}")
    
    def _render_type(self, type_: StaticType) -> str:
        if isinstance(type_, TupleT):
            inner = ", ".join(self._render_type(arg) for arg in type_.args)
            return f"std::tuple<{inner}>"
        return f"ap_uint<{type_.total_bits()}>"
    
    def _cast(self, type_: StaticType, expr: str) -> str:
        return f"{self._render_type(type_)}({expr})"
    
    def _emit_temp(self, type_: StaticType, expr: str, comment: str) -> _CppValue:
        temp_name = f"tmp_{self._temp_index}"
        self._temp_index += 1
        cpp_type = self._render_type(type_)
        self._statements.append(f"const {cpp_type} {temp_name} = {expr};  // {comment}")
        return _CppValue(expr=temp_name, cpp_type=cpp_type)
    
    def _bit_mask(self, width: int) -> str:
        return self._cast(UQT(width, 0), str((1 << width) - 1))


def lower_to_cpp(root: Node, function_name: str = "compute") -> str:
    emitter = _CppEmitter()
    return emitter.emit_function(root=root, function_name=function_name)
