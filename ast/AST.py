from typing import Any, Callable, Tuple
from fused_dot_product.types.types import Type
from fused_dot_product.utils.utils import ulp_distance

class Node: 
    def evaluate(self) -> Tuple[Type, Any]:
        raise NotImplementedError
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        """Abstract print method for subclasses."""
        raise NotImplementedError

# Computational tree
class Composite(Node):
    def __init__(
        self, 
        spec: Callable, # specification (mathematical definition)
        impl: Node, # implementation (composite of Op)
        args: list[Node], # operands
        name: str, # composite's name
    ):
        self.spec, self.impl, self.args, self.name = spec, impl, args, name
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.name} [Composite]")

        new_prefix = prefix + ("    " if is_last else "│   ")

        # If depth > 0, print Impl and skip Args
        if depth > 0:
            print(new_prefix + "└── Impl:")
            self.impl.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            # Otherwise, print Args as before
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)

    def evaluate(self) -> Tuple[Type, Any]:
        # that's dumb, self.args get evaluated twice, for impl and spec
        spec_inputs = []
        impl_inputs = []
        for arg in self.args:
            impl_, spec_ = arg.evaluate()
            spec_inputs.append(spec_)
            impl_inputs.append(impl_)
            
        composite_spec = self.spec(*spec_inputs)
        impl_res, spec_res = self.impl.evaluate()
         
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
        
        if ulp_distance(composite_spec, spec_res) != 0:
            raise AssertionError(err_msg)
        elif ulp_distance(spec_res, impl_res.to_spec()) != 0:
            raise AssertionError(err_msg)

        return impl_res, composite_spec
        
    def evaluate_spec(self):
        vals = []
        for arg in self.args:
            vals.append(arg.evaluate()[1])
        return self.spec(*vals)
      
class Op(Node):
    def __init__(
        self, 
        spec: Callable[..., Any], # specification (mathematical definition)
        impl: Callable[..., Any], # implementation (actual execution)
        args: list[Node], # operands
        name: str, # op's name
        cost: int = 1 # op's cost
    ):
        self.spec, self.impl, self.args, self.name, self.cost = spec, impl, args, name, cost
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.name} [Op]")
        new_prefix = prefix + ("    " if is_last else "│   ")
        for i, arg in enumerate(self.args):
            is_arg_last = i == len(self.args) - 1
            arg.print_tree(new_prefix, is_arg_last, depth)

    # TODO: create a constant node!
    def evaluate(self) -> Tuple[Type, Any]:
        spec_inputs = []
        impl_inputs = []
        for arg in self.args:
            impl_, spec_ = arg.evaluate()
            spec_inputs.append(spec_)
            impl_inputs.append(impl_)
        
        impl_res = self.impl(*impl_inputs)
        spec_res = self.spec(*spec_inputs)
        err_msg = (
            f"[{self.name}] mismatch:\n"
            f"  input-spec: {spec_inputs}\n"
            f"  input-impl: {[str(x) for x in impl_inputs]}\n"
            f"  impl: {impl_res}\n"
            f"  spec: {spec_res}\n"
            f"  spec/impl ulp: {ulp_distance(impl_res.to_spec(), spec_res)}"
        )
        
        if ulp_distance(spec_res, impl_res.to_spec()) != 0:
            raise AssertionError(err_msg)
        
        return impl_res, spec_res

class Const(Node):
    def __init__(self, 
                 val: Type, 
                 name: str = None):
        assert isinstance(val, Type), f"Const's val must be a Type, {val} is provided"
        self.name, self.val = name, val
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.name if self.name else str(self.val)} [Const]")
        
    def evaluate(self) -> Tuple[Type, Any]:
        return self.val, self.val.to_spec()

class Var(Node):
    def __init__(self, name: str, val: Any = None):
        self.name, self.val = name, val
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.name} [Var]")
        
    def load_val(self, val: Type):
        assert isinstance(val, Type), f"Var's val must be a Type, {val} is provided"
        self.val = val
        
    def __str__(self):
        return f"{str(self.val)} [Var]"
        
    def evaluate(self) -> Tuple[Type, Any]:
        if self.val is None:
            raise ValueError(f"Variable {self.name} not bound to a value")
        return self.val, self.val.to_spec()

