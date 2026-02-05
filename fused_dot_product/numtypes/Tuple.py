from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *
import inspect

def make_Tuple(*args: Node) -> Primitive:
    if not args:
        raise TypeError("Tuple cannot be empty")

    def sign(*args: StaticType) -> TupleT:
        return TupleT(*args)
    
    sign_fixed = _make_fixed_arguments(sign, StaticType, len(args))
    
    def impl(*nodes: Node) -> Node:
        def op(*vals: RuntimeType) -> Tuple:
            return Tuple(*vals)
        return Op(
            impl=_make_fixed_arguments(op, RuntimeType, len(nodes)),
            sign=sign_fixed,
            args=[*nodes],
            name=f"basic_tuple_maker_{len(nodes)}",
        )
    
    def spec(prim, *args, s):
        return tuple(args)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign_fixed,
        args=args,
        name="make_Tuple")


# Helper function for creating annotation with fixed number of arguments
def _make_fixed_arguments(f, default_type, N):

    # Desired signature parameters
    params = [
        inspect.Parameter(
            f"arg{i}",
            inspect.Parameter.POSITIONAL_ONLY,
            annotation=default_type,
        )
        for i in range(N)
    ]

    ret_ann = f.__annotations__.get("return", inspect._empty)

    sig = inspect.Signature(
        parameters=params,
        return_annotation=ret_ann,
    )

    # ---- wrapper that enforces strict arity ----
    def wrapper(*args):
        if len(args) != N:
            raise TypeError(f"{f.__name__} expects {N} arguments, got {len(args)}")
        return f(*args)  # f expects N args too

    # Apply signature + metadata
    wrapper.__signature__ = sig
    wrapper.__annotations__ = {
        **{f"arg{i}": default_type for i in range(N)},
        "return": ret_ann,
    }
    wrapper.__name__ = f.__name__
    wrapper.__qualname__ = f.__qualname__
    wrapper.__doc__ = f.__doc__

    return wrapper



if __name__ == '__main__':
    x = Const(Int(2))
    y = Const(Int(3))
    make_Tuple(x, y).print_tree()
