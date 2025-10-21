from typing import Any

# Computational tree
class CTree:
    def __init__(self):
        self.smth = 0

    def __call__(self, pt):
        return 0

class Operator:
    def __init__(self, spec, impl, comp, args, name):
        self.spec = spec  # specification (mathematical definition)
        self.impl = impl  # implementation (actual execution)
        self.comp = comp  # converter
        self.args = args  # operands 
        self.name = name  # operator's name

    def evaluate(self):
        vals = [a.evaluate() if isinstance(a, Operator) else a for a in self.args]
        
        spec_res = self.spec(*vals)
        impl_res = self.impl(*vals)
        assert self.comp(spec_res) == self.comp(impl_res)
        return impl_res

    def print_tree(self, prefix: str = "", is_last: bool = True):
        """Print the AST in a 'tree' command-like style."""
        connector = "└── " if is_last else "├── "
        print(prefix + connector + self.name)

        # Prepare new prefix for children
        new_prefix = prefix + ("    " if is_last else "│   ")
        for i, arg in enumerate(self.args):
            is_arg_last = (i == len(self.args) - 1)
            if isinstance(arg, Operator):
                arg.print_tree(new_prefix, is_arg_last)
            else:
                leaf_connector = "└── " if is_arg_last else "├── "
                print(new_prefix + leaf_connector + self._arg_str(arg))
        
    def _arg_str(self, arg: Any) -> str:
        if isinstance(arg, Operator):
            return arg.name
        return repr(arg)

# Decorator for Operator class
def operator(spec, comp=lambda x: x):
    return lambda impl: Operator(spec=spec, impl=impl, comp=comp)

