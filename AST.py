# Computational tree
class CTree:
    def __init__(self):
        self.smth = 0

    def __call__(self, pt):
        return 0

class Node:
    def __init__(self, spec=None, 
                       comp=lambda x: x, 
                       pre=[], 
                       post=[], 
                       impl=None):
        assert isinstance(pre, list)
        for p in pre:
            assert callable(p)
        assert callable(comp)
        assert callable(spec)
        assert isinstance(post, list)
        for p in post:
            assert callable(p)
            
        self.specification = spec
        self.implementation = impl
        self.comparator = comp
        self.pre_conditions = pre
        self.post_conditions = post

    def __call__(self, *args):
        if self.implementation is None:
            if callable(args[0]) and len(args) == 1:
                func = args[0]
                return Node(spec=self.specification, 
                            comp=self.comparator,
                            pre=self.pre_conditions,
                            post=self.post_conditions,
                            impl=func)
            else:
                raise TypeError("impl is not provided for Node")
        else:
            for pre in self.pre_conditions:
                assert pre(*args)
                
            spec_res = self.specification(*args)
            impl_res = self.implementation(*args)
            assert self.comparator(spec_res) == self.comparator(impl_res)
            
            for post in self.post_conditions:
                assert post(impl_res)
            return impl_res
