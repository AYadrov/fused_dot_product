import inspect
import typing as tp
from contextvars import ContextVar

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.utils.utils import ulp_distance


class Node:
    # Shared cache for a single evaluation call-chain.
    _eval_cache: ContextVar[tp.Optional[dict["Node", RuntimeType]]] = ContextVar(
        "eval_cache", default=None
    )

    def __init__(self, spec: tp.Callable[..., tp.Any],
                       impl: tp.Callable[..., RuntimeType],
                       sign: tp.Callable[..., StaticType],
                       args: list["Node"],
                       name: str):
        self.spec = spec
        self.impl = impl
        self.sign = sign
        self.args = args
        self.name = name
        
        # Defines node_type at initialization - some parts rely on this
        self.static_typecheck()
    
    def copy(self):
        return Copy(self)
    
    def __getitem__(self, idx):
        return Tuple_get_item(self, idx)
    
    def evaluate(self, cache: tp.Optional[dict["Node", RuntimeType]] = None) -> RuntimeType:
        # Use a per-evaluation cache to avoid recomputing shared subtrees.
        # Cache lives only for the current call chain.
        active_cache = cache if cache is not None else self._eval_cache.get()
        if active_cache is None:
            active_cache = {}
        token = self._eval_cache.set(active_cache)
        
        try:
            if self in active_cache:
                return active_cache[self]
            
            inputs = [arg.evaluate(active_cache) for arg in self.args]
            out = self.impl(*inputs)
            
            ########## CHECK BLOCK #########
            self.dynamic_typecheck(args=inputs, out=out)
            
            if self.spec:
                spec_inputs = [x.to_spec() for x in inputs]
                spec_out = self.spec(*spec_inputs)
                err_msg = (
                    f"[{self.name}] mismatch:\n"
                    f"  input-spec: {spec_inputs}\n"
                    f"  input-impl: {[str(x) for x in inputs]}\n"
                    f"  impl: {out}\n"
                    f"  spec: {spec_out}\n"
                    f"  spec/impl ulp: {ulp_distance(out.to_spec(), spec_out)}"
                )
                assert ulp_distance(spec_out, out.to_spec()) == 0, err_msg
            ################################
            active_cache[self] = out
            return out
            
        finally:
            self._eval_cache.reset(token)
    
    def static_typecheck(self, verify=False):
        # Checks that signature's annotations are StaticType
        self.primitive_signature_check()
        
        self.args_types = [x.static_typecheck() if verify else x.node_type for x in self.args]
        self.node_type = self.sign(*self.args_types)
        
        # Checks that signature does match with received args_types and node_type
        self.signature_match(args=self.args_types, out=self.node_type)
        
        ####### CONSTANT FOLDING #######
        runtime_vals = [arg.runtime_val for arg in self.args_types]
        if all([val is not None for val in runtime_vals]) and runtime_vals != []:
            constant_fold = self.impl(*runtime_vals)
            self.dynamic_typecheck(args=runtime_vals, out=constant_fold)
            self.node_type.runtime_val = constant_fold
        ################################
        
        return self.node_type
    
    def dynamic_typecheck(self, args: list[RuntimeType], out: RuntimeType):
        err_msg = (
            f"Arguments do not match Node's signature at {self.name}:\n"
            f"  Given: {[x.static_type() for x in args]}\n"
            f"  Required: {self.args_types}\n"
        )
        for arg, arg_t in zip(args, self.args_types):
            assert arg.static_type() == arg_t, err_msg
        
        err_msg = (
            f"Output does not match Node's signature at {self.name}:\n"
            f"  impl: {out}\n"
            f"  impl-type: {out.static_type()}\n"
            f"  expected-type: {self.node_type}\n"
        )
        assert out.static_type() == self.node_type, err_msg
    
    def primitive_signature_check(self):
        sign = inspect.signature(self.sign)
        err_msg = (
            f"Signature contain types that are not an instance of StaticType!\n"
            f"Given: {sign}\n"
        )
        for param in sign.parameters.values():
            assert issubclass(param.annotation, StaticType), err_msg
        assert issubclass(sign.return_annotation, StaticType), err_msg
    
    def signature_match(self, args: list[StaticType], out: StaticType):
        sign = inspect.signature(self.sign)
        args_msg = (
            f"Arguments to {self.name} do not match its signature\n"
            f"Given: {args}\n"
            f"Required: {[param.annotation for param in sign.parameters.values()]}\n"
        )
        for param, arg_type in zip(sign.parameters.values(), args):
            assert isinstance(arg_type, param.annotation), args_msg
        output_msg = (
            f"Output from {self.name} does not match its signature\n"
            f"Given: {out}\n"
            f"Required: {sign.return_annotation}"
        )
        assert isinstance(out, sign.return_annotation), output_msg
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        raise NotImplementedError


class Composite(Node):
    def __init__(self, spec: tp.Callable[..., tp.Any],
                       impl: Node,
                       sign: tp.Callable[..., StaticType],
                       args: list[Node],
                       name: str):
        self.impl_pt = impl(*args)  # Pointer to the full tree for traverses/printing
        
        variables = [Var(name=f"arg_{i}", sign=x.node_type) for i, x in enumerate(args)]
        inner_tree = impl(*variables)  # Pointer to the Composite's inner tree
        
        def impl_(*args):
            for var, arg in zip(variables, args):
                var.load_val(arg)
            return inner_tree.evaluate()
        
        super().__init__(spec=spec,
                         impl=impl_,
                         sign=sign,
                         args=args,
                         name=name)


    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Composite]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            self.impl_pt.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)


# Currently looks the same as Composite
class Primitive(Node):
    def __init__(self, spec: tp.Callable[..., tp.Any],
                       impl: Node,
                       sign: tp.Callable[..., StaticType],
                       args: list[Node],
                       name: str):
        self.impl_pt = impl(*args)  # Pointer to the full tree for traverses/printing
        
        variables = [Var(name=f"arg_{i}", sign=x.node_type) for i, x in enumerate(args)]
        inner_tree = impl(*variables)  # Pointer to the inner tree
        
        def impl_(*args):
            for var, arg in zip(variables, args):
                var.load_val(arg)
            return inner_tree.evaluate()
        
        super().__init__(spec=spec,
                         impl=impl_,
                         sign=sign,
                         args=args,
                         name=name)

    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Primitive]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            self.impl_pt.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)


class Op(Node):
    def __init__(
        self,
        impl: tp.Callable[..., RuntimeType],
        sign: tp.Callable[..., StaticType],
        args: list[Node],
        name: str,
    ):
        super().__init__(spec=None,
                         impl=impl,
                         sign=sign,
                         args=args,
                         name=name)
    
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
    def __init__(self, 
                 val: RuntimeType, 
                 name: str = ""):
        self.val = val
        
        def impl():
            return self.val
        
        def spec():
            return self.val.to_spec()
        
        def sign() -> StaticType:
            node_type = self.val.static_type()
            node_type.runtime_val = self.val  # Constant folding for typechecking
            return node_type
        
        super().__init__(spec=spec,
                         impl=impl,
                         sign=sign,
                         args=[],
                         name=name)
    
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
        
        def spec():
            assert self.val is not None, f"Variable {self.name} not bound to a value"
            return self.val.to_spec()
        
        def signature() -> StaticType:
            return sign
        
        super().__init__(spec=spec,
                         impl=impl,
                         sign=signature,
                         args=[],
                         name=name)
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Var]")
    
    def load_val(self, val: RuntimeType):
        assert isinstance(val, RuntimeType), f"Var's val must be a RuntimeType, {val} is provided"
        self.val = val
    
    def __str__(self):
        return f"{self.node_type}: {self.name} [Var]"


def Copy(x: Node) -> Op:
    def sign(x: StaticType) -> StaticType:
        return x
    
    def impl(x):
        return x.copy()
    
    return Op(
        sign=sign,
        impl=impl,
        args=[x],
        name="Copy")


# TODO: to be moved somewhere, it's here due to loading cycles
def Tuple_get_item(x: Node, idx: int) -> Op:
    def sign(x: TupleT) -> StaticType:
        if not isinstance(x, TupleT):
            raise TypeError(f"{x} is not an instance of TupleT to iterate over it")
        return x.args[idx]

    def impl(x: Tuple) -> RuntimeType:
        if idx >= len(x.args) or idx < 0:
            raise ValueError(f"Index is out of range for tuple {str(x)}, given {str(idx)}")
        return x.args[idx]

    return Op(
        impl=impl,
        sign=sign,
        args=[x],
        name="Tuple_get_item")

