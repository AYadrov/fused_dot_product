from typing import Any

# Computational tree
class CTree:
    def __init__(self):
        self.smth = 0

    def __call__(self, pt):
        return 0

class Operator:
    def __init__(self, spec, impl, comp, args, name, cost=0):
        self.spec = spec  # specification (mathematical definition)
        self.impl = impl  # implementation (actual execution)
        self.comp = comp  # converter
        self.args = args  # operands
        self.name = name  # operator's name
        self.cost = cost

    def evaluate(self):
        vals = [a.evaluate() if isinstance(a, Operator) else a for a in self.args]
        
        spec_res = self.spec(*vals)
        impl_res = self.impl(*vals)
        assert self.comp(spec_res) == self.comp(impl_res), \
            f"Operator {self.name}'s spec and impl evaluations do not match for input: {vals}"
        return impl_res

    def print_tree(self, prefix: str = "", is_last: bool = True):
        """Print the AST in a Linux 'tree'-like style with module visualization."""
        connector = "└── " if is_last else "├── "
        is_module = isinstance(self.impl, Operator)

        # Print this node
        if is_module:
            print(prefix + connector + f"{self.name} (Module) ──┤")
            # Compute new prefix for the module’s own internal tree
            module_prefix = prefix + ("    " if is_last else "│   ")
            # Indent extra spaces to visually align the vertical bar after ──┤
            module_indent = " " * (len(self.name) + len(" (Module) ──┤") - 1)
            self.impl.print_tree(prefix=module_prefix + module_indent, is_last=True)
        else:
            print(prefix + connector + self.name + " (Custom)")
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

