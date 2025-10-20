# Computational tree
class CTree:
    def __init__(self):
        self.smth = 0

    def __call__(self, pt):
        return 0
        


class Operator:
    def __init__(self, spec=None,
                       comp=lambda x: x,
                       impl=None,
                       args=[]):
        assert callable(comp)
        assert callable(spec)
        assert callable(impl) or impl is None
        assert isinstance(args, list)
        
        self.specification = spec
        self.implementation = impl
        self.comparator = comp
        self.args = args

    def evaluate(self):
        vals = [a.evaluate() if isinstance(a, Operator) else a for a in self.args]
        
        spec_res = self.specification(*vals)
        impl_res = self.implementation(*vals)
        assert self.comparator(spec_res) == self.comparator(impl_res)
        return impl_res

# Decorator for Operator class
def operator(spec, comp=lambda x: x):
    return lambda impl: Operator(spec=spec, impl=impl, comp=comp)

