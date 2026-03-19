import inspect
import typing as tp
from contextvars import ContextVar

from ..types.runtime import Bool, RuntimeType
from ..types.static import BoolT, StaticType
from ..spec import *


def _is_static_type_annotation(annotation: tp.Any) -> bool:
    return isinstance(annotation, type) and issubclass(annotation, StaticType)


class Node:
    _eval_cache: ContextVar[tp.Optional[dict["Node", RuntimeType]]] = ContextVar(
        "eval_cache", default=None
    )

    def __init__(
        self,
        spec: tp.Callable[..., tp.Any],
        impl: tp.Callable[..., RuntimeType],
        sign: tp.Callable[..., StaticType],
        args: list["Node"],
        name: str,
    ):
        if not all(isinstance(x, Node) for x in args):
            bad_args = [type(x).__name__ for x in args if not isinstance(x, Node)]
            raise TypeError(f"Node arguments must be Node instances, got {bad_args}")
        # Checks that signature's annotations are StaticType
        self._primitive_signature_check(sign)
        
        # Wrapper for impl that makes sure that out always matches node_type
        def impl_wrapper(impl):
            def compute(inputs: list[RuntimeType]):
                out = None
                if self.node_type.runtime_val is not None:
                    out = self.node_type.runtime_val  # constant-folded nodes are already checked for type
                else:
                    out = impl(*inputs)
                    self._dynamic_typecheck(inputs=inputs, out=out)
                return out.copy()
            
            return compute
        
        self.spec = spec
        self.impl = impl_wrapper(impl)
        self.sign = sign
        self.args = args
        self.name = name
        
        # Defines node_type at initialization - some parts rely on this
        self._static_typecheck()
    
    ############## PRIVATE METHODS ###############
       
    def _evaluate_spec(self, ctx, cache):
        if self in cache:
            return cache[self]
        inputs = [arg._evaluate_spec(ctx, cache) for arg in self.args]
        output = self.spec(*inputs, ctx=ctx)
        cache[self] = output
        return output
    
    def _static_typecheck(self):
        # Clone to avoid sharing runtime_val/state across nodes.
        self.args_types = [x.node_type.copy() for x in self.args]  # runtime_val is preserved
        self.node_type = self.sign(*self.args_types).copy()
        self.node_type.runtime_val = None  # Do not preserve runtime_val for output
        
        # Checks that signature does match with received args_types and node_type
        self._signature_match(args=self.args_types, out=self.node_type)
        
        # Constant folding
        # If all arguments are known at compile time - apply constant folding
        args_ = [arg.runtime_val for arg in self.args_types]
        if all([val is not None for val in args_]) and args_ != []:
            self.node_type.runtime_val = self.impl(args_)

        return self.node_type

    def _dynamic_typecheck(self, inputs: list[RuntimeType], out: RuntimeType):
        if len(inputs) != len(self.args_types):
            raise TypeError(
                f"Arguments do not match Node's signature at {self.name}:\n"
                f"  Given count: {len(inputs)}\n"
                f"  Required count: {len(self.args_types)}\n"
            )

        err_msg = (
            f"Arguments do not match Node's signature at {self.name}:\n"
            f"  Given: {[x.static_type() for x in inputs]}\n"
            f"  Required: {self.args_types}\n"
        )
        for arg, arg_t in zip(inputs, self.args_types):
            if arg.static_type() != arg_t:
                raise TypeError(err_msg)

        if not isinstance(out, RuntimeType):
            raise TypeError(
                f"Output does not match Node's signature at {self.name}:\n"
                f"  impl returned non-RuntimeType: {type(out).__name__}\n"
                f"  expected-type: {self.node_type}\n"
            )

        err_msg = (
            f"Output does not match Node's signature at {self.name}:\n"
            f"  impl: {out}\n"
            f"  impl-type: {out.static_type()}\n"
            f"  expected-type: {self.node_type}\n"
        )
        if out.static_type() != self.node_type:
            raise TypeError(err_msg)

    def _primitive_signature_check(self, sign):
        sign = inspect.signature(sign)
        err_msg = (
            f"Signature contain types that are not an instance of StaticType!\n"
            f"Given: {sign}\n"
        )
        for param in sign.parameters.values():
            if not _is_static_type_annotation(param.annotation):
                raise TypeError(err_msg)
        if not _is_static_type_annotation(sign.return_annotation):
            raise TypeError(err_msg)

    def _signature_match(self, args: list[StaticType], out: StaticType):
        sign = inspect.signature(self.sign)
        if len(args) != len(sign.parameters):
            raise TypeError(
                f"Arguments to {self.name} do not match its signature\n"
                f"Given count: {len(args)}\n"
                f"Required count: {len(sign.parameters)}\n"
            )
        args_msg = (
            f"Arguments to {self.name} do not match its signature\n"
            f"Given: {args}\n"
            f"Required: {[param.annotation for param in sign.parameters.values()]}\n"
        )
        for param, arg_type in zip(sign.parameters.values(), args):
            if not isinstance(arg_type, param.annotation):
                raise TypeError(args_msg)
        output_msg = (
            f"Output from {self.name} does not match its signature\n"
            f"Given: {out}\n"
            f"Required: {sign.return_annotation}"
        )
        if not isinstance(out, sign.return_annotation):
            raise TypeError(output_msg)

    ################ PUBLIC API ##################
    
    def copy(self):
        from .helpers import Copy
        return Copy(self)
    
    def __getitem__(self, idx: int):
        from .helpers import Tuple_get_item
        return Tuple_get_item(self, idx)
    
    def evaluate(self, cache: tp.Optional[dict["Node", RuntimeType]] = None) -> RuntimeType:
        # Use a per-evaluation cache to avoid recomputing shared subtrees.
        # Cache lives only for the current call chain.
        active_cache = cache if cache is not None else self._eval_cache.get()
        if active_cache is None:
            active_cache = {}
        token = self._eval_cache.set(active_cache)
        
        try:
            # Cache hit
            if self in active_cache:
                return active_cache[self].copy()
            
            inputs = [arg.evaluate(active_cache) for arg in self.args]
            out = self.impl(inputs)
            active_cache[self] = out
            
            return out
        
        finally:
            # Erase current cache
            self._eval_cache.reset(token)

    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        raise NotImplementedError
