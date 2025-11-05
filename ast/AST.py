from typing import Any, Callable

# from fused_dot_product.ast.types import *

class Node: 
    def evaluate(self) -> tuple[Any, Any]:
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
                if isinstance(arg, Node):
                    arg.print_tree(new_prefix, is_arg_last, depth)
                else:
                    leaf_connector = "└── " if is_arg_last else "├── "
                    print(new_prefix + leaf_connector + repr(arg))


    def evaluate(self) -> tuple[Any, Any]:
        # that's dumb, self.args get evaluated twice, for impl and spec
        spec_inputs = []
        for arg in self.args:
            if isinstance(arg, Node):
                _, spec_ = arg.evaluate()
                spec_inputs.append(spec_)
            else:
                spec_inputs.append(arg)
        composite_spec = self.spec(*spec_inputs)
        impl_res, spec_res = self.impl.evaluate()
        
        if spec_res != impl_res.to_spec() or composite_spec != spec_res:
            raise AssertionError(
                f"[{self.name}] mismatch:\n"
                f"  input: {spec_inputs}\n"
                f"  impl: {impl_res}\n"
                f"  spec: {spec_res}\n"
                f"  composite_spec: {composite_spec}"
            )

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
            if isinstance(arg, Node):
                arg.print_tree(new_prefix, is_arg_last, depth)
            else:
                leaf_connector = "└── " if is_arg_last else "├── "
                print(new_prefix + leaf_connector + repr(arg))

    # TODO: create a constant node!
    def evaluate(self) -> tuple[Any, Any]:
        spec_inputs = []
        impl_inputs = []
        for arg in self.args:
            impl_, spec_ = arg.evaluate()
            spec_inputs.append(spec_)
            impl_inputs.append(impl_)
        
        impl_res = self.impl(*impl_inputs)
        spec_res = self.spec(*spec_inputs)
        
        return impl_res, spec_res

class Const(Node):
    def __init__(self, 
                 val: Any, # Type, 
                 name: str = None):
        # assert isinstance(val, Type), f"Const val must be a Type, {val} is provided"
        self.name, self.val = name, val
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.name if self.name else str(self.val)} [Const]")
        
    def evaluate(self):
        return self.val, self.val.to_spec()

class Var(Node):
    def __init__(self, name: str, val: Any = None):
        self.name, self.val = name, val
        
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.name} [Var]")
        
    def load_val(self, val):
        self.val = val
        
    def evaluate(self) -> tuple[Any, Any]:
        if self.val is None:
            raise ValueError(f"Variable {self.name} not bound to a value")
        return self.val, self.val.to_spec()

