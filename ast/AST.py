from typing import Any, Callable, Tuple
import inspect

from fused_dot_product.numtypes.RuntimeTypes import RuntimeType
from fused_dot_product.numtypes.StaticTypes import StaticType
from fused_dot_product.utils.utils import ulp_distance

class Node:
    def evaluate(self) -> Tuple[RuntimeType, Any]:
        raise NotImplementedError
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        raise NotImplementedError
    
    def static_typecheck(self):
        raise NotImplementedError
        
    def dynamic_typecheck(self, impl_res):
        err_msg = (
            f"Produced value does not match node_type at Node: {self.name}:\n"
            f"  impl: {impl_res}\n"
            f"  impl-type: {impl_res.static_type()}\n"
            f"  expected-type: {self.node_type}"
        )
        assert impl_res.static_type() == self.node_type, err_msg


class Composite(Node):
    def __init__(
        self,
        spec: Callable[..., Any],
        impl: Node,
        args: list[Node],
        name: str,
    ):
        self.spec, self.impl, self.args, self.name = spec, impl, args, name
        self.node_type = self.static_typecheck()
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Composite]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            self.impl.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)
    
    def evaluate(self) -> Tuple[RuntimeType, Any]:
        # that's dumb, self.args get evaluated twice, for impl and spec
        spec_inputs = []
        impl_inputs = []
        for arg in self.args:
            impl_, spec_ = arg.evaluate()
            spec_inputs.append(spec_)
            impl_inputs.append(impl_)
        
        composite_spec = self.spec(*spec_inputs)
        impl_res, spec_res = self.impl.evaluate()
        
        ########## CHECK BLOCK #########
        self.dynamic_typecheck(impl_res)
        err_msg = (
            f"[{self.name}] mismatch:\n"
            f"  input-spec: {spec_inputs}\n"
            f"  input-impl: {[str(x) for x in impl_inputs]}\n"
            f"  impl: {impl_res}\n"
            f"  spec: {spec_res}\n"
            f"  composite_spec: {composite_spec}\n"
            f"  spec/impl ulp: {ulp_distance(impl_res.to_spec(), spec_res)}"
            f"  composite_spec/impl ulp: {ulp_distance(impl_res.to_spec(), composite_spec)}"
        )
        assert ulp_distance(composite_spec, spec_res) == 0, err_msg
        assert ulp_distance(spec_res, impl_res.to_spec()) == 0, err_msg
        ################################
        
        return impl_res, composite_spec
    
    def static_typecheck(self):
        return self.impl.static_typecheck()  # or self.impl.node_type - it is faster


class Op(Node):
    def __init__(
        self,
        spec: Callable[..., Any],
        impl: Callable[..., RuntimeType],
        signature: Callable[..., StaticType],
        args: list[Node],
        name: str,
    ):
        self.spec, self.impl, self.signature, self.args, self.name = spec, impl, signature, args, name
        self.node_type = self.static_typecheck()
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Op]")
        new_prefix = prefix + ("    " if is_last else "│   ")
        for i, arg in enumerate(self.args):
            is_arg_last = i == len(self.args) - 1
            arg.print_tree(new_prefix, is_arg_last, depth)
    
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
        ######## SIGNATURE CHECK #######
        sign = inspect.signature(self.signature)
        err_msg = (
            f"Signature contain types that are not an instance of StaticType at Op: {self.name}!\n"
            f"Given: {sign}"
        )
        for param in sign.parameters.values():
            assert issubclass(param.annotation, StaticType), err_msg
        assert issubclass(sign.return_annotation, StaticType), err_msg
        ################################
        
        args_types = [x.static_typecheck() for x in self.args]
        node_type = self.signature(*args_types)
        
        ######## SIGNATURE MATCH #######
        args_msg = (
            f"Arguments to Op: {self.name} do not match its signature\n"
            f"Given: {args_types}\n"
            f"Required: {[param.annotation for param in sign.parameters.values()]}"
        )
        for param, arg_type in zip(sign.parameters.values(), args_types):
            assert isinstance(arg_type, param.annotation), args_msg
        output_msg = (
            f"Output from Op:{self.name} does not match its signature\n"
            f"Given: {node_type}\n"
            f"Required: {sign.return_annotation}"
        )
        assert isinstance(node_type, sign.return_annotation), output_msg
        ################################
        
        ####### CONSTANT FOLDING #######
        self.node_type = node_type
        runtime_vals = [arg.runtime_val for arg in args_types]
        if all(runtime_vals):
            constant_fold = self.impl(*runtime_vals)
            self.dynamic_typecheck(constant_fold)
            node_type.runtime_val = constant_fold
        ################################
        
        return node_type


class Const(Node):
    def __init__(self, 
                 val: RuntimeType, 
                 name: str = None):
        self.val, self.name = val, name
        self.node_type = self.static_typecheck()
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + self.__str__())
    
    def __str__(self):
        return f"{self.node_type}: {self.name if self.name else str(self.val)} [Const]"
    
    def evaluate(self) -> Tuple[RuntimeType, Any]:
        self.dynamic_typecheck(self.val)
        return self.val, self.val.to_spec()
    
    def static_typecheck(self):
        assert isinstance(self.val, RuntimeType), f"Const's val must be a RuntimeType, {self.val} is provided"
        node_type = self.val.static_type()
        assert isinstance(node_type, StaticType), f"Const node value's type is not an instance of StaticType, given: {self.val}, type: {self.val.static_type()}"
        node_type.runtime_val = self.val  # Constant folding for static typechecking
        return node_type


class Var(Node):
    def __init__(self, name: str, signature: StaticType):
        self.name, self.signature = name, signature
        self.node_type = self.static_typecheck()
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Var]")
        
    def load_val(self, val: RuntimeType):
        assert isinstance(val, RuntimeType), f"Var's val must be a RuntimeType, {val} is provided"
        self.val = val
        
    def __str__(self):
        return f"{self.node_type}: {self.name} [Var]"
        
    def evaluate(self) -> Tuple[RuntimeType, Any]:
        assert self.val is not None, f"Variable {self.name} not bound to a value"
        self.dynamic_typecheck(self.val)
        return self.val, self.val.to_spec()
    
    def static_typecheck(self):
        assert isinstance(self.signature, StaticType), f"Const node value is not an instance of StaticType, given: {signature}"
        return self.signature

