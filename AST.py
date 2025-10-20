# Computational tree
class CTree:
    def __init__(self):
        self.smth = 0

    def __call__(self, pt):
        return 0

class Operator:
    def __init__(self, spec=None,
                       comp=lambda x: x,
                       impl=None):
        assert callable(comp)
        assert callable(spec)
        assert callable(impl) or impl is None
        
        self.specification = spec
        self.implementation = impl
        self.comparator = comp

    def __call__(self, *args):
        if self.implementation is None:
            raise ValueError("implementation is not provided for operator")
        spec_res = self.specification(*args)
        impl_res = self.implementation(*args)
        assert self.comparator(spec_res) == self.comparator(impl_res)
        return impl_res

# Decorator for Operator class
def operator(spec, comp=lambda x: x):
    return lambda impl: Operator(spec=spec, impl=impl, comp=comp)

