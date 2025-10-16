# Computational tree
class CTree:
    def __init__(self):
        self.smth = 0

    def __call__(self, pt):
        return 0

class Node:
    def __init__(self, spec, impl, comp=lambda x: x):
        self.spec = spec
        self.impl = impl
        self.comparator = comp

    def __call__(self, *args):
        spec_res = self.spec(*args)
        impl_res = self.impl(*args)
        assert self.comparator(spec_res) == self.comparator(impl_res)
        return impl_res
