import inspect
import typing as tp
from contextvars import ContextVar

from ..numtypes.RuntimeTypes import Bool, RuntimeType, Tuple
from ..numtypes.StaticTypes import BoolT, StaticType, TupleT
from ..utils.utils import ulp_distance
from ..numtypes.z3_utils import *

from cvc5.pythonic import Solver, FreshReal, unsat, sat, RealVal, unknown, SolverFor


class Node:
    # Shared cache for a single evaluation call-chain.
    _eval_cache: ContextVar[tp.Optional[dict["Node", RuntimeType]]] = ContextVar(
        "eval_cache", default=None
    )
    
    def __init__(self, spec: tp.Callable[..., tp.Any],
                       impl: tp.Callable[..., RuntimeType],
                       sign: tp.Callable[..., StaticType],
                       args: list["Node"],
                       name: str):
        assert all([isinstance(x, Node) for x in args])
        # Checks that signature's annotations are StaticType
        self._primitive_signature_check(sign)
        
        # Wrapper for impl that makes sure that out always matches node_type and satisfies spec
        def compute(inputs: list[RuntimeType]):
            out = None
            if self.node_type.runtime_val is not None:
                out = self.node_type.runtime_val  # constantly-folded nodes are already checked for type and spec
            else:
                out = impl(*inputs)
                self._dynamic_typecheck(inputs=inputs, out=out)
                # self.run_spec_checks(inputs=inputs, out=out)
            return out.copy()
        
        self.spec = spec
        self.impl = compute
        self.sign = sign
        self.args = args
        self.name = name
        self._assert_statements = []
        
        # Defines node_type at initialization - some parts rely on this
        self._static_typecheck()
        
    ############## PRIVATE METHODS ###############
    
    def run_spec_checks(self, s=None, cache=None):
        print(self.name, self.args)

        if cache is None:
            cache = {}
        if self in cache:
            return cache[self]
        if isinstance(self, Composite):
            s = Solver() if s is None else s
            
            # s.setOption("use-portfolio", "true")
            # s.setOption("portfolio-jobs", "4")

            s.add(*pow2_props)
            
            inputs = []
            for arg in self.inner_args:
                inputs.append(arg.run_spec_checks(s, cache))
            
            out_ = self.inner_tree.run_spec_checks(s, cache)
            out = self.spec(*inputs, s=s)
            
            # Check that outer spec is not equal to inner spec
            # The result should be unsat
            s.add(out != out_)
            cache[self] = out
            
            print(s.sexpr())
            
            res = s.check()
            print(res)
            
            if res == unsat:
                print ("proved")
            elif res == unknown:
                print(s.reason_unknown())
            else:
                model = s.model()
                print ("failed to prove")
                print(f"Counterexample found:\n{model}")
            
            return out
        elif isinstance(self, Primitive):
            inputs = []
            for child in self.args:
                inputs.append(child.run_spec_checks(s, cache))
            out = self.spec(*inputs, s=s)
            cache[self] = out
            return out
        elif isinstance(self, Var):
            out = self.node_type.to_smt(s)
            cache[self] = out
            return out
        elif isinstance(self, Const):
            out = self.node_type.runtime_val.to_smt(s)
            cache[self] = out
            return out
        else:
            raise TypeError(f"Found an Op {self.name}. Please, make sure that the provided tree does not contain an Op")
    
    def _run_asserts(self, cache=None):
        for to_assert in self._assert_statements:
            res = to_assert.evaluate(cache)
            assert isinstance(res, Bool)
            if res.val == 0:
                raise AssertionError(f"Assertion mismatch at {to_assert.name} for {self.name}")
    
    def _static_typecheck(self):
        # Clone to avoid sharing runtime_val/state across nodes.
        self.args_types = [x.node_type.copy() for x in self.args]  # runtime_val is preserved
        self.node_type = self.sign(*self.args_types).copy()
        self.node_type.runtime_val = None  # Do not preserve runtime_val for output
        
        # Checks that signature does match with received args_types and node_type
        self._signature_match(args=self.args_types, out=self.node_type)
        
        # Constant folding
        # If all arguments are known at compile time - apply constant folding
        args_ = [arg.runtime_val for arg in self.args_types]
        if all([val is not None for val in args_]) and args_ != []:
            self.node_type.runtime_val = self.impl(args_)
        
        return self.node_type
    
    def _dynamic_typecheck(self, inputs: list[RuntimeType], out: RuntimeType):
        err_msg = (
            f"Arguments do not match Node's signature at {self.name}:\n"
            f"  Given: {[x.static_type() for x in inputs]}\n"
            f"  Required: {self.args_types}\n"
        )
        for arg, arg_t in zip(inputs, self.args_types):
            assert arg.static_type() == arg_t, err_msg
        
        err_msg = (
            f"Output does not match Node's signature at {self.name}:\n"
            f"  impl: {out}\n"
            f"  impl-type: {out.static_type()}\n"
            f"  expected-type: {self.node_type}\n"
        )
        assert out.static_type() == self.node_type, err_msg
    
    def _primitive_signature_check(self, sign):
        sign = inspect.signature(sign)
        err_msg = (
            f"Signature contain types that are not an instance of StaticType!\n"
            f"Given: {sign}\n"
        )
        for param in sign.parameters.values():
            assert issubclass(param.annotation, StaticType), err_msg
        assert issubclass(sign.return_annotation, StaticType), err_msg
    
    def _signature_match(self, args: list[StaticType], out: StaticType):
        sign = inspect.signature(self.sign)
        args_msg = (
            f"Arguments to {self.name} do not match its signature\n"
            f"Given: {args}\n"
            f"Required: {[param.annotation for param in sign.parameters.values()]}\n"
        )
        for param, arg_type in zip(sign.parameters.values(), args):
            assert isinstance(arg_type, param.annotation), args_msg
        output_msg = (
            f"Output from {self.name} does not match its signature\n"
            f"Given: {out}\n"
            f"Required: {sign.return_annotation}"
        )
        assert isinstance(out, sign.return_annotation), output_msg
    
    ################ PUBLIC API ##################
    
    def copy(self):
        return Copy(self)
    
    def __getitem__(self, idx: int):
        return Tuple_get_item(self, idx)
    
    def check(self, assert_node: "Node"):
        assert isinstance(assert_node, Node)
        assert assert_node.node_type == BoolT()
        assert len(assert_node.args) != 0, f"No arguments provided for assert {assert_node.name}"
        self._assert_statements.append(assert_node)
    
    def evaluate(self, cache: tp.Optional[dict["Node", RuntimeType]] = None) -> RuntimeType:
        # Use a per-evaluation cache to avoid recomputing shared subtrees.
        # Cache lives only for the current call chain.
        active_cache = cache if cache is not None else self._eval_cache.get()
        if active_cache is None:
            active_cache = {}
        token = self._eval_cache.set(active_cache)
        
        try:
            # Cache hit, Node is checked with asserts
            if self in active_cache:
                return active_cache[self].copy()
            
            inputs = [arg.evaluate(active_cache) for arg in self.args]
            out = self.impl(inputs)
            active_cache[self] = out  # run_asserts can refer to itself causing infinite loop, caching prevents it
            
            self._run_asserts(cache=active_cache)
            
            return out
        
        finally:
            # Erase current cache
            self._eval_cache.reset(token)
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        raise NotImplementedError


class Composite(Node):
    def __init__(self, spec: tp.Callable[..., tp.Any],
                       impl: Node,
                       sign: tp.Callable[..., StaticType],
                       args: list[Node],
                       name: str):
        # Pointer to the full tree for traverses/printing
        self.printing_helper = impl
        
        # Args will preserve runtime values of arguments
        self.inner_args = [Const(name=f"arg_{i}", val=x.node_type.runtime_val) if x.node_type.runtime_val is not None else Var(name=f"arg_{i}", sign=x.node_type.copy()) for i, x in enumerate(args)]
        # Pointer to the inner tree
        self.inner_tree = impl(*self.inner_args)
        
        def impl_(*args):
            for var, arg in zip(self.inner_args, args):
                if isinstance(var, Var):
                    var.load_val(arg)
            return self.inner_tree.evaluate()
        
        super().__init__(spec=spec,
                         impl=impl_,
                         sign=sign,
                         args=args,
                         name=name)
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        impl_pt = self.printing_helper(*self.args)  # Constructing a whole tree
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Composite]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            impl_pt.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)


# Currently looks the same as Composite
class Primitive(Node):
    def __init__(self, spec: tp.Callable[..., tp.Any],
                       impl: Node,
                       sign: tp.Callable[..., StaticType],
                       args: list[Node],
                       name: str):
        # Pointer to the full tree for traverses/printing
        self.printing_helper = impl
        
        # Args will preserve runtime values of arguments
        self.inner_args = [Const(name=f"arg_{i}", val=x.node_type.runtime_val) if x.node_type.runtime_val is not None else Var(name=f"arg_{i}", sign=x.node_type.copy()) for i, x in enumerate(args)]
        # Pointer to the inner tree
        self.inner_tree = impl(*self.inner_args)
        
        def impl_(*args):
            for var, arg in zip(self.inner_args, args):
                if isinstance(var, Var):
                    var.load_val(arg)
            return self.inner_tree.evaluate()
        
        super().__init__(spec=spec,
                         impl=impl_,
                         sign=sign,
                         args=args,
                         name=name)
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        impl_pt = self.printing_helper(*self.args)  # Constructing a whole tree
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Primitive]")
        
        new_prefix = prefix + ("    " if is_last else "│   ")
        
        if depth > 0:
            print(new_prefix + "└── Impl:")
            impl_pt.print_tree(new_prefix + "    ", True, depth - 1)
        else:
            for i, arg in enumerate(self.args):
                is_arg_last = i == len(self.args) - 1
                arg.print_tree(new_prefix, is_arg_last, depth)


class Op(Node):
    def __init__(
        self,
        impl: tp.Callable[..., RuntimeType],
        sign: tp.Callable[..., StaticType],
        args: list[Node],
        name: str,
    ):
        super().__init__(spec=None,
                         impl=impl,
                         sign=sign,
                         args=args,
                         name=name)
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + self.__str__())
        new_prefix = prefix + ("    " if is_last else "│   ")
        for i, arg in enumerate(self.args):
            is_arg_last = i == len(self.args) - 1
            arg.print_tree(new_prefix, is_arg_last, depth)
    
    def __str__(self):
        return f"{self.node_type}: {self.name} [Op]"


class Const(Node):
    def __init__(self,
                 val: RuntimeType,
                 name: str = ""):
        self.val = val
        
        def impl():
            return self.val
        
        def spec(out):
            return self.val.to_spec() == out
        
        def sign() -> StaticType:
            return self.val.static_type()
        
        super().__init__(spec=spec,
                         impl=impl,
                         sign=sign,
                         args=[],
                         name=name)
        
        self.node_type.runtime_val = self.val  # Constant folding
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + self.__str__())
    
    def __str__(self):
        return f"{self.node_type}: {self.name if self.name else str(self.val)} [Const]"


class Var(Node):
    def __init__(self, name: str, sign: StaticType):
        self.val = None
        
        def impl():
            assert self.val is not None, f"Variable {self.name} not bound to a value"
            return self.val
        
        def spec(out):
            assert self.val is not None, f"Variable {self.name} not bound to a value"
            return self.val.to_spec() == out
        
        def signature() -> StaticType:
            return sign
        
        super().__init__(spec=spec,
                         impl=impl,
                         sign=signature,
                         args=[],
                         name=name)
    
    def print_tree(self, prefix: str = "", is_last: bool = True, depth: int = 0):
        connector = "└── " if is_last else "├── "
        print(prefix + connector + f"{self.node_type}: {self.name} [Var]")
    
    def load_val(self, val: RuntimeType):
        assert isinstance(val, RuntimeType), f"Var's val must be a RuntimeType, {val} is provided"
        self.val = val
    
    def __str__(self):
        return f"{self.node_type}: {self.name} [Var]"


def Copy(x: Node) -> Primitive:
    def sign(x: StaticType) -> StaticType:
        return x
    
    def spec(x, s):
        return x
    
    def impl(x):
        return x
    
    return Primitive(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="Copy")


# TODO: to be moved somewhere, it's here due to loading cycles
def Tuple_get_item(x: Node, idx: int) -> Primitive:
    if idx >= len(x.node_type.args) or idx < 0:
        raise IndexError(f"Index is out of range for tuple {str(x)}, given {str(idx)}")
    
    def sign(x: TupleT) -> StaticType:
        if not isinstance(x, TupleT):
            raise IndexError(f"{x} is not an instance of TupleT to iterate over it")
        return x.args[idx]

    def impl(x: Node) -> Node:
        from fused_dot_product.numtypes.basics import _unary_operator
        def basic_get_item(x: Node, out: Node) -> Op:
            return _unary_operator(
                op=lambda x: x.args[idx].val,
                x=x,
                out=out,
                name="basic_get_item",
            )
        return basic_get_item(x, Const(x.node_type.args[idx].runtime_type()))
    
    def spec(x, s):
        return x[idx]

    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name=f"Tuple_get_item_{idx}")
