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


def make_fixed_arguments(f, default_type, N):

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
