from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *

def make_Tuple(*args: Node) -> Op:
    def spec(*args):
        return tuple(args)
    
    def impl(*args: RuntimeType) -> Tuple:
        return Tuple(*args)
    
    def sign(*args: StaticType) -> TupleT:
        return TupleT(*args)
    
    return Op(
        spec=spec,
        impl=make_fixed_arguments(impl, RuntimeType, len(args)),
        signature=make_fixed_arguments(sign, StaticType, len(args)),
        args=args,
        name="Tuple_create")
        
if __name__ == '__main__':
    x = Const(Int(2))
    y = Const(Int(3))
    make_Tuple(x, y).print_tree()
