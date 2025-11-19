import inspect
from typing import Any, Callable, Tuple

from fused_dot_product.numtypes.RuntimeTypes import RuntimeType
from fused_dot_product.numtypes.StaticTypes import StaticType
from fused_dot_product.utils.utils import ulp_distance


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
        self.dynamic_typecheck(args=impl_inputs, out=impl_res)
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
    
    def static_typecheck(self, verify=False):
        # Checks that signature's annotations are StaticType
        self.primitive_signature_check()
        
        self.args_types = [x.static_typecheck() if verify else x.node_type for x in self.args]
        self.node_type = self.signature(*self.args_types)
        
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
        sign = inspect.signature(self.signature)
        err_msg = (
            f"Signature contain types that are not an instance of StaticType!\n"
            f"Given: {sign}\n"
        )
        for param in sign.parameters.values():
            assert issubclass(param.annotation, StaticType), err_msg
        assert issubclass(sign.return_annotation, StaticType), err_msg
    
    def signature_match(self, args: list[StaticType], out: StaticType):
        sign = inspect.signature(self.signature)
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
    def __init__(self, spec: Callable[..., Any],
                       impl: Node,
                       sign: Callable[..., StaticType],
                       args: list[Node],
                       name: str):
        self.impl_pt = impl
        
        # TODO: impl gets evaluated twice!
        def impl_(*args):
            return self.impl_pt.evaluate()[0]  # drop spec evaluation as Composite has its own spec
        
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
        
        def sign() -> StaticType:
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
        
        def sign() -> StaticType:
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

