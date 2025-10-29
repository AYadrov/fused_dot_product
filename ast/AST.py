from typing import Any, Callable

class Node: 
    def evaluate(self) -> tuple[Any, Any]:
        raise NotImplementedError

# Computational tree
class Composite(Node):
    def __init__(
        self, 
        spec: Callable, # specification (mathematical definition)
        impl: Node, # implementation (composite of Op)
        args: list[Any], # operands
        name: str, # composite's name
    ):
        self.spec, self.impl, self.args, self.name = spec, impl, args, name
    
    # def print_tree(self, prefix: str = "", is_last: bool = True):
    #     
    #     self.empty_check()
    #     self.root.print_tree()
    
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
        
        if spec_res != impl_res or composite_spec != spec_res:
            raise AssertionError(
                f"[{self.name}] mismatch:\n"
                f"  input: {spec_inputs}\n"
                f"  impl: {impl_res}\n"
                f"  spec: {spec_res}\n"
                f"  composite_spec: {composite_spec}"
            )

        return impl_res, composite_spec
      
class Op(Node):
    def __init__(
        self, 
        spec: Callable[..., Any], # specification (mathematical definition)
        impl: Callable[..., Any], # implementation (actual execution)
        args: list[Any], # operands
        name: str, # op's name
        cost: int = 1 # op's cost
    ):
        self.spec, self.impl, self.args, self.name, self.cost = spec, impl, args, name, cost

    # TODO: create a constant node!
    def evaluate(self) -> tuple[Any, Any]:
        spec_inputs = []
        impl_inputs = []
        for arg in self.args:
            if isinstance(arg, Node):
                impl_, spec_ = arg.evaluate()
                spec_inputs.append(spec_)
                impl_inputs.append(impl_)
            else:
                spec_inputs.append(arg)
                impl_inputs.append(arg)
        
        impl_res = self.impl(*impl_inputs)
        spec_res = self.spec(*spec_inputs)
        
        return impl_res, spec_res
    
    def evaluate_spec(self):
        vals = []
        for arg in self.args:
            if isinstance(arg, Node):
                vals.append(arg.evaluate()[1])
            else:
                vals.append(arg)
        return self.spec(*vals)

    # def print_tree(self, prefix: str = "", is_last: bool = True):
    #     """Print the AST in a Linux 'tree'-like style with module visualization."""
    #     connector = "└── " if is_last else "├── "
    #
    #     print(prefix + connector + self.name)
    #     # Prepare new prefix for children
    #     new_prefix = prefix + ("    " if is_last else "│   ")
    #     for i, arg in enumerate(self.args):
    #         is_arg_last = (i == len(self.args) - 1)
    #         if isinstance(arg, Op):
    #             arg.print_tree(new_prefix, is_arg_last)
    #         else:
    #             leaf_connector = "└── " if is_arg_last else "├── "
    #             print(new_prefix + leaf_connector + self._arg_str(arg))

    # def _arg_str(self, arg: Any) -> str:
    #     if isinstance(arg, Op):
    #         return arg.name
    #     elif isinstance(arg, Var):
    #         return arg.name
    #     else:
    #         return repr(arg)
        
class Var(Node):
    def __init__(self, name: str, val: Any = None):
        self.name, self.val = name, val
    
    def load_val(self, val):
        self.val = val
        
    def evaluate(self) -> tuple[Any, Any]:
        if self.val is None:
            raise ValueError(f"Variable {self.name} not bound to a value")
        return self.val, self.val

