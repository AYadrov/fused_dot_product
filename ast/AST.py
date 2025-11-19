from typing import Any, Callable, Tuple

from fused_dot_product.numtypes.RuntimeTypes import RuntimeType
from fused_dot_product.numtypes.StaticTypes import StaticType
from fused_dot_product.utils.utils import ulp_distance


# TODO: Static typechecking of input arguments
class Node:
    def __init__(self, spec: Callable[..., Any],
                       impl: Callable[..., RuntimeType],
                       sign: Callable[..., StaticType],
                       args: list["Node"],
                       name: str):
        self.spec = spec
        self.impl = impl
        self.signature = sign
        self.args = args
        self.name = name
        
        self.static_typecheck()
    
    def evaluate(self) -> Tuple[RuntimeType, Any]:
        spec_inputs = []
        impl_inputs = []
        for arg in self.args:
            impl_, spec_ = arg.evaluate()
            spec_inputs.append(spec_)
            impl_inputs.append(impl_)
        
        impl_res = self.impl(*impl_inputs)
        spec_res = self.spec(*spec_inputs)
        
        ########## CHECK BLOCK #########
        self.dynamic_typecheck(impl_res)
        err_msg = (
            f"[{self.name}] mismatch:\n"
            f"  input-spec: {spec_inputs}\n"
            f"  input-impl: {[str(x) for x in impl_inputs]}\n"
            f"  impl: {impl_res}\n"
            f"  spec: {spec_res}\n"
            f"  spec/impl ulp: {ulp_distance(impl_res.to_spec(), spec_res)}"
        )
        assert ulp_distance(spec_res, impl_res.to_spec()) == 0, err_msg
        ################################
        return impl_res, spec_res
    
    def static_typecheck(self):
        args_types = [x.node_type for x in self.args]
        self.node_type = self.signature(*args_types)
        
        for t in args_types:
            assert isinstance(t, StaticType), \
                "Argument to {self.name} has a type that is not an instance of StaticType: {t}"
        assert isinstance(self.node_type, StaticType), \
                "Output of {self.name} has a type that is not an instance of StaticType: {self.node_type}"
        
        ####### CONSTANT FOLDING #######
        runtime_vals = [arg.runtime_val for arg in args_types]
        if all(runtime_vals) and runtime_vals != []:
            constant_fold = self.impl(*runtime_vals)
            self.dynamic_typecheck(constant_fold)
            self.node_type.runtime_val = constant_fold
        ################################
        
    def dynamic_typecheck(self, impl_res):
        err_msg = (
            f"Produced value does not match node_type at Node: {self.name}:\n"
            f"  impl: {impl_res}\n"
            f"  impl-type: {impl_res.static_type()}\n"
            f"  expected-type: {self.node_type}"
        )
        assert impl_res.static_type() == self.node_type, err_msg
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        raise NotImplementedError


class Composite(Node):
    def __init__(self, spec: Callable[..., Any],
                       impl: Node,
                       args: list[Node],
                       name: str):
        self.impl_pt = impl
        
        def impl_(*args):
            return self.impl_pt.evaluate()[0]  # drop spec evaluation as Composite has its own spec
        
        def sign(*args_types):
            return self.impl_pt.node_type
        
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


class Op(Node):
    def __init__(
        self,
        spec: Callable[..., Any],
        impl: Callable[..., RuntimeType],
        signature: Callable[..., StaticType],
        args: list[Node],
        name: str,
    ):
        super().__init__(spec=spec,
                         impl=impl,
                         sign=signature,
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
        
        def sign():
            node_type = self.val.static_type()
            node_type.runtime_val = self.val  # Constant folding at typechecking
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
    def __init__(self, name: str, signature: StaticType):
        self.val = None
        
        def impl():
            assert self.val is not None, f"Variable {self.name} not bound to a value"
            return self.val
        
        def spec():
            assert self.val is not None, f"Variable {self.name} not bound to a value"
            return self.val.to_spec()
        
        def sign():
            return signature
        
        super().__init__(spec=spec,
                         impl=impl,
                         sign=sign,
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
