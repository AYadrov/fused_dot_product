import typing as tp

from ..types.runtime import RuntimeType
from ..types.static import StaticType
from ..utils import make_fixed_arguments
from .node import Node
from .proofs import ProofRecorder, record_proofs
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
        # Pointer to the full tree for traverses/printing
        self.printing_helper = impl
        
        self.inner_args = [Var(name=f"arg_{i}", sign=x.node_type.copy()) for i, x in enumerate(args)]
        
        self.ctx = SpecContext(name)
        self.spec_ctx = {}
        
        recorder = ProofRecorder(self.ctx, self.spec_ctx)
        with record_proofs(recorder):
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
        
    
    def check_spec(self, z3_timeout_ms: int = 60000, egglog_iters=5):
        cache = {}
        
        spec_inner = self.inner_tree._evaluate_spec(ctx=self.ctx, cache=cache)
        
        inputs = [arg._evaluate_spec(ctx=self.ctx, cache=cache) for arg in self.inner_args]
        spec_outer = self.spec(*inputs, ctx=self.ctx)
        
        certificate = check_equivalence(
            spec_inner,
            spec_outer,
            ctx=self.ctx,
            egglog_iters=egglog_iters,
            z3_timeout_ms=z3_timeout_ms,
        )
        return certificate
    
    
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
        # Pointer to the full tree for traverses/printing
        self.printing_helper = impl
        
        # Args will preserve runtime values of arguments
        self.inner_args = [Var(name=f"arg_{i}", sign=x.node_type.copy()) for i, x in enumerate(args)]
        # Pointer to the inner tree
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
        impl_pt = self.printing_helper(*self.args)  # Constructing a whole tree
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Primitive]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            impl_pt.print_tree(new_prefix + "    ", True, depth - 1)
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
            assert self.val is not None, f"Variable {self.name} not bound to a value"
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
        assert isinstance(val, RuntimeType), f"Var's val must be a RuntimeType, {val} is provided"
        self.val = val
    
    def __str__(self):
        return f"{self.node_type}: {self.name} [Var]"
    
