import typing as tp

from ..types.runtime import RuntimeType
from ..types.static import StaticType
from ..utils import make_fixed_arguments
from .node import Node
from .proofs import SpecRecorder, record_specs
from ..solver import check_equivalence
from ..spec import SpecContext


def Composite(name: str, spec: tp.Callable[..., tp.Any]):
    def wrapper1(impl: tp.Callable[..., Node]):
        def wrapper2(*args):
            return composite(spec=spec, impl=impl, args=args, name=name)
        return wrapper2
    return wrapper1

class composite(Node):
    def __init__(
        self,
        spec: tp.Callable[..., tp.Any],
        impl: tp.Callable[..., Node],
        args: list[Node],
        name: str,
    ):
        self.ctx = SpecContext(name)
        self.inner_args = [Var(name=f"arg_{i}", sign=x.node_type.copy()) for i, x in enumerate(args)]
        
        recorder = SpecRecorder(self.ctx)
        with record_specs(recorder):
            self.inner_tree = impl(*self.inner_args)
        
        self._validate_components(name)
        
        def impl_(*args):
            for var, arg in zip(self.inner_args, args):
                if isinstance(var, Var):
                    var.load_val(arg)
            return self.inner_tree.evaluate()
        
        # Signature is obtained from the inner tree
        def sign(*args):
            return self.inner_tree.node_type
        
        sign = make_fixed_arguments(
            sign,
            arg_types=[type(x.node_type) for x in args],
            return_type=type(self.inner_tree.node_type),
        )
        
        super().__init__(
            spec=spec,
            impl=impl_,
            sign=sign,
            args=args,
            name=name,
        )
    
    
    def check_spec(self, z3_timeout_ms: int = 5000, egglog_iters=6):
        ctx = self.ctx.copy()
        spec_inner = ctx.spec_of(self.inner_tree)
        
        inputs = [ctx.spec_of(arg) for arg in self.inner_args]
        spec_outer = self.spec(*inputs, ctx=ctx)
        
        equivalence, proof_trace = check_equivalence(
            spec_inner,
            spec_outer,
            ctx=ctx,
            egglog_iters=egglog_iters,
            z3_timeout_ms=z3_timeout_ms,
            dreal_precision=0.001,
        )
        return proof_trace

    def _validate_components(self, composite_name: str) -> None:
        visited: set[Node] = set()

        def visit(node: Node, path: str) -> None:
            if node in visited:
                return
            visited.add(node)

            if isinstance(node, (primitive, composite)):
                for idx, arg in enumerate(node.args):
                    visit(arg, f"{path} -> {node.name}.arg[{idx}]")
                return

            if isinstance(node, (Var, Const)):
                return

            raise TypeError(
                f"Composite {composite_name} must be composed recursively of Primitive/Composite nodes; "
                f"found {type(node).__name__} {node.name!r} at {path}"
            )

        visit(self.inner_tree, f"{composite_name}.impl")
    
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Composite]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            self.inner_tree.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)
        
    def __str__(self):
        return f"[Composite] {self.name}: {' -> '.join([str(x) for x in self.args_types])} -> {self.node_type}"


def Primitive(name: str, spec: tp.Callable[..., tp.Any]):
    def wrapper1(impl: tp.Callable[..., Node]):
        def wrapper2(*args):
            return primitive(spec=spec, impl=impl, args=args, name=name)
        return wrapper2
    return wrapper1

class primitive(Node):
    def __init__(
        self,
        spec: tp.Callable[..., tp.Any],
        impl: tp.Callable[..., Node],
        args: list[Node],
        name: str,
    ):
        # Args will preserve runtime values of arguments
        self.inner_args = [Var(name=f"arg_{i}", sign=x.node_type.copy()) for i, x in enumerate(args)]
        
        self.inner_tree = impl(*self.inner_args)
        
        def impl_(*args):
            for var, arg in zip(self.inner_args, args):
                if isinstance(var, Var):
                    var.load_val(arg)
            return self.inner_tree.evaluate()
        
        # Signature is obtained from the inner tree
        def sign(*args):
            return self.inner_tree.node_type
        
        sign = make_fixed_arguments(
            sign,
            arg_types=[type(x.node_type) for x in args],
            return_type=type(self.inner_tree.node_type),
        )
        
        super().__init__(
            spec=spec,
            impl=impl_,
            sign=sign,
            args=args,
            name=name,
        )
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Primitive]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            self.inner_tree.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)
    
    def __str__(self):
        return f"[Primitive] {self.name}: {' -> '.join([str(x) for x in self.args_types])} -> {self.node_type}"


class Op(Node):
    def __init__(
        self,
        impl: tp.Callable[..., RuntimeType],
        sign: tp.Callable[..., StaticType],
        args: list[Node],
        name: str,
    ):
        super().__init__(
            spec=None,
            impl=impl,
            sign=sign,
            args=args,
            name=name,
        )
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + self.__str__())
        new_prefix = prefix + ("    " if is_last else "│   ")
        for i, arg in enumerate(self.args):
            is_arg_last = i == len(self.args) - 1
            arg.print_tree(new_prefix, is_arg_last, depth)
    
    def __str__(self):
        return f"{self.node_type}: {self.name} [Op]"


class Const(Node):
    def __init__(
        self,
        val: RuntimeType,
    ):
        self.val = val
        
        def impl():
            return self.val
        
        def spec(ctx):
            return self.val.to_spec(ctx)
        
        def sign() -> StaticType:
            return self.val.static_type()
        
        super().__init__(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[],
            name=str(self.val.to_val()),
        )
        
        self.node_type.runtime_val = self.val  # Constant folding
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + self.__str__())
    
    def __str__(self):
        return f"{self.node_type}: {self.name if self.name else str(self.val)} [Const]"


class Var(Node):
    def __init__(self, name: str, sign: StaticType):
        self.val = None
        
        def impl():
            if self.val is None:
                raise ValueError(f"Variable {self.name} not bound to a value")
            return self.val
        
        def spec(ctx):
            return sign.to_spec(self.name, ctx)
        
        def signature() -> StaticType:
            return sign
        
        super().__init__(
            spec=spec,
            impl=impl,
            sign=signature,
            args=[],
            name=name,
        )
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Var]")
    
    def load_val(self, val: RuntimeType):
        if not isinstance(val, RuntimeType):
            raise TypeError(f"Var's val must be a RuntimeType, {val} is provided")
        if val.static_type() != self.sign():
            raise TypeError(f"Var's val does not match signature {self.sign()}, {val.static_type()} is provided")
        self.val = val
    
    def __str__(self):
        return f"{self.node_type}: {self.name} [Var]"
    
