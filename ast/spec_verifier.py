import importlib.util
import inspect
import sysconfig
import textwrap
import typing as tp

from fused_dot_product.ast.AST import Composite, Const, Node, Op, Primitive, Var

# Standard library ast is shadowed by this package name; load it explicitly.
_ast_spec = importlib.util.find_spec("ast", [sysconfig.get_paths()["stdlib"]])
if _ast_spec is None or _ast_spec.loader is None:
    raise ImportError("Could not locate stdlib ast module")
_stdlib_ast = importlib.util.module_from_spec(_ast_spec)
_ast_spec.loader.exec_module(_stdlib_ast)
ast = _stdlib_ast


########## Symbolic core ##########


class SymBase:
    def simplify(self) -> "SymBase":
        return self

    def contains(self, target: "SymBase") -> bool:
        return self is target

    # Arithmetic
    def __add__(self, other):
        return SymOp("add", self, to_sym(other))

    def __radd__(self, other):
        return to_sym(other).__add__(self)

    def __sub__(self, other):
        return SymOp("sub", self, to_sym(other))

    def __rsub__(self, other):
        return to_sym(other).__sub__(self)

    def __mul__(self, other):
        return SymOp("mul", self, to_sym(other))

    def __rmul__(self, other):
        return to_sym(other).__mul__(self)

    def __truediv__(self, other):
        return SymOp("truediv", self, to_sym(other))

    def __rtruediv__(self, other):
        return to_sym(other).__truediv__(self)

    def __floordiv__(self, other):
        return SymOp("floordiv", self, to_sym(other))

    def __rfloordiv__(self, other):
        return to_sym(other).__floordiv__(self)

    def __pow__(self, power, modulo=None):
        return SymOp("pow", self, to_sym(power))

    def __rpow__(self, other):
        return to_sym(other).__pow__(self)

    def __lshift__(self, other):
        return SymOp("lshift", self, to_sym(other))

    def __rshift__(self, other):
        return SymOp("rshift", self, to_sym(other))

    def __and__(self, other):
        return SymOp("and_bits", self, to_sym(other))

    def __or__(self, other):
        return SymOp("or_bits", self, to_sym(other))

    def __xor__(self, other):
        return SymOp("xor_bits", self, to_sym(other))

    def __invert__(self):
        return SymOp("invert", self)

    def __neg__(self):
        return SymOp("neg", self)

    # Comparisons
    def __eq__(self, other):
        return SymEq(self, to_sym(other))

    def __ne__(self, other):
        return SymNot(SymEq(self, to_sym(other)))

    def __lt__(self, other):
        return SymCmp("lt", self, to_sym(other))

    def __le__(self, other):
        return SymCmp("le", self, to_sym(other))

    def __gt__(self, other):
        return SymCmp("gt", self, to_sym(other))

    def __ge__(self, other):
        return SymCmp("ge", self, to_sym(other))

    def __bool__(self):
        raise TypeError("Symbolic expressions cannot be converted to bool")


class SymConst(SymBase):
    def __init__(self, value: tp.Any):
        self.value = value

    def simplify(self):
        return self

    def contains(self, target: SymBase) -> bool:
        return self is target

    def __repr__(self):
        return f"Const({self.value!r})"


class SymVar(SymBase):
    def __init__(self, name: str, typ: tp.Optional[object] = None):
        self.name = name
        self.typ = typ

    def __getitem__(self, item):
        return SymIndex(self, item)

    def simplify(self):
        return self

    def contains(self, target: SymBase) -> bool:
        return self is target

    def __repr__(self):
        return self.name


class SymIndex(SymBase):
    def __init__(self, base: SymBase, idx: int):
        self.base = base
        self.idx = idx

    def simplify(self):
        return SymIndex(self.base.simplify(), self.idx)

    def contains(self, target: SymBase) -> bool:
        return self.base.contains(target)

    def __repr__(self):
        return f"{self.base}[{self.idx}]"


class SymTuple(SymBase):
    def __init__(self, items: tp.Sequence[SymBase]):
        self.items = tuple(items)

    def __getitem__(self, item):
        return self.items[item]

    def simplify(self):
        return SymTuple([x.simplify() for x in self.items])

    def contains(self, target: SymBase) -> bool:
        return any(x.contains(target) for x in self.items)

    def __repr__(self):
        return f"Tuple({', '.join(repr(x) for x in self.items)})"


class SymOp(SymBase):
    def __init__(self, op: str, *args: SymBase):
        self.op = op
        self.args = args

    def simplify(self):
        args = [a.simplify() for a in self.args]
        if all(isinstance(a, SymConst) for a in args):
            vals = [a.value for a in args]  # type: ignore[attr-defined]
            return SymConst(_eval_op(self.op, vals))
        return SymOp(self.op, *args)

    def contains(self, target: SymBase) -> bool:
        return any(a.contains(target) for a in self.args)

    def __repr__(self):
        return f"{self.op}({', '.join(repr(a) for a in self.args)})"


class SymEq(SymBase):
    def __init__(self, left: SymBase, right: SymBase):
        self.left = left
        self.right = right

    def simplify(self):
        left = self.left.simplify()
        right = self.right.simplify()
        if isinstance(left, SymConst) and isinstance(right, SymConst):
            return SymBoolConst(left.value == right.value)
        if _expr_structurally_equal(left, right):
            return SymBoolConst(True)
        return SymEq(left, right)

    def contains(self, target: SymBase) -> bool:
        return self.left.contains(target) or self.right.contains(target)

    def __repr__(self):
        return f"Eq({self.left!r}, {self.right!r})"


class SymCmp(SymBase):
    def __init__(self, op: str, left: SymBase, right: SymBase):
        self.op = op
        self.left = left
        self.right = right

    def simplify(self):
        left = self.left.simplify()
        right = self.right.simplify()
        if isinstance(left, SymConst) and isinstance(right, SymConst):
            return SymBoolConst(_eval_cmp(self.op, left.value, right.value))
        return SymCmp(self.op, left, right)

    def contains(self, target: SymBase) -> bool:
        return self.left.contains(target) or self.right.contains(target)

    def __repr__(self):
        return f"{self.op}({self.left!r}, {self.right!r})"


class SymBoolConst(SymBase):
    def __init__(self, value: bool):
        self.value = bool(value)

    def simplify(self):
        return self

    def contains(self, target: SymBase) -> bool:
        return False

    def __bool__(self):
        return self.value

    def __repr__(self):
        return f"Bool({self.value})"


class SymBoolOp(SymBase):
    def __init__(self, op: str, args: tp.Sequence[SymBase]):
        self.op = op
        self.args = list(args)

    def simplify(self):
        args = [to_sym_bool(a).simplify() for a in self.args]
        if self.op == "and":
            flat = []
            for a in args:
                if isinstance(a, SymBoolConst) and a.value is True:
                    continue
                if isinstance(a, SymBoolConst) and a.value is False:
                    return SymBoolConst(False)
                if isinstance(a, SymBoolOp) and a.op == "and":
                    flat.extend(a.args)
                else:
                    flat.append(a)
            if not flat:
                return SymBoolConst(True)
            if len(flat) == 1:
                return flat[0]
            return SymBoolOp("and", flat)
        elif self.op == "or":
            flat = []
            for a in args:
                if isinstance(a, SymBoolConst) and a.value is False:
                    continue
                if isinstance(a, SymBoolConst) and a.value is True:
                    return SymBoolConst(True)
                if isinstance(a, SymBoolOp) and a.op == "or":
                    flat.extend(a.args)
                else:
                    flat.append(a)
            if not flat:
                return SymBoolConst(False)
            if len(flat) == 1:
                return flat[0]
            return SymBoolOp("or", flat)
        return SymBoolOp(self.op, args)

    def contains(self, target: SymBase) -> bool:
        return any(a.contains(target) for a in self.args)

    def __repr__(self):
        return f"{self.op.upper()}({', '.join(repr(a) for a in self.args)})"


class SymNot(SymBase):
    def __init__(self, expr: SymBase):
        self.expr = expr

    def simplify(self):
        expr = to_sym_bool(self.expr).simplify()
        if isinstance(expr, SymBoolConst):
            return SymBoolConst(not expr.value)
        return SymNot(expr)

    def contains(self, target: SymBase) -> bool:
        return self.expr.contains(target)

    def __repr__(self):
        return f"NOT({self.expr!r})"


class SymIf(SymBase):
    def __init__(self, cond: SymBase, true_val: SymBase, false_val: SymBase):
        self.cond = cond
        self.true_val = true_val
        self.false_val = false_val

    def simplify(self):
        cond = to_sym_bool(self.cond).simplify()
        if isinstance(cond, SymBoolConst):
            return self.true_val.simplify() if cond.value else self.false_val.simplify()
        return SymIf(cond, self.true_val.simplify(), self.false_val.simplify())

    def contains(self, target: SymBase) -> bool:
        return (
            self.cond.contains(target)
            or self.true_val.contains(target)
            or self.false_val.contains(target)
        )

    def __repr__(self):
        return f"IF({self.cond!r}, {self.true_val!r}, {self.false_val!r})"


class SymCall(SymBase):
    def __init__(self, func_name: str, args: tp.Sequence[SymBase]):
        self.func_name = func_name
        self.args = list(args)

    def simplify(self):
        args = [a.simplify() for a in self.args]
        if all(isinstance(a, SymConst) for a in args):
            vals = [a.value for a in args]  # type: ignore[attr-defined]
            fn = _FUNCTION_REGISTRY.get(self.func_name)
            if fn is not None:
                return SymConst(fn(*vals))
        return SymCall(self.func_name, args)

    def contains(self, target: SymBase) -> bool:
        return any(a.contains(target) for a in self.args)

    def __repr__(self):
        return f"{self.func_name}({', '.join(repr(a) for a in self.args)})"


def to_sym(val: tp.Any) -> SymBase:
    if isinstance(val, SymBase):
        return val
    if isinstance(val, tuple):
        return SymTuple([to_sym(x) for x in val])
    if isinstance(val, (int, float, bool)):
        return SymConst(val)
    raise TypeError(f"Unsupported symbolic value: {val} ({type(val)})")


def to_sym_bool(val: tp.Any) -> SymBase:
    if isinstance(val, SymBoolConst):
        return val
    if isinstance(val, SymBase):
        if isinstance(val, SymConst) and not isinstance(val.value, bool):
            return SymBoolConst(bool(val.value))
        return val
    return SymBoolConst(bool(val))


def _expr_structurally_equal(a: SymBase, b: SymBase) -> bool:
    if type(a) is not type(b):
        return False
    if isinstance(a, SymConst):
        return a.value == b.value  # type: ignore[attr-defined]
    if isinstance(a, SymVar):
        return a.name == b.name
    if isinstance(a, SymIndex):
        return a.idx == b.idx and _expr_structurally_equal(a.base, b.base)
    if isinstance(a, SymTuple):
        return len(a.items) == len(b.items) and all(
            _expr_structurally_equal(x, y) for x, y in zip(a.items, b.items)
        )
    if isinstance(a, SymOp):
        return a.op == b.op and all(
            _expr_structurally_equal(x, y) for x, y in zip(a.args, b.args)
        )
    if isinstance(a, SymEq):
        return _expr_structurally_equal(a.left, b.left) and _expr_structurally_equal(
            a.right, b.right
        )
    if isinstance(a, SymCmp):
        return a.op == b.op and _expr_structurally_equal(a.left, b.left) and _expr_structurally_equal(a.right, b.right)
    if isinstance(a, SymBoolConst):
        return a.value == b.value  # type: ignore[attr-defined]
    if isinstance(a, SymBoolOp):
        return a.op == b.op and len(a.args) == len(b.args) and all(
            _expr_structurally_equal(x, y) for x, y in zip(a.args, b.args)
        )
    if isinstance(a, SymNot):
        return _expr_structurally_equal(a.expr, b.expr)
    if isinstance(a, SymIf):
        return (
            _expr_structurally_equal(a.cond, b.cond)
            and _expr_structurally_equal(a.true_val, b.true_val)
            and _expr_structurally_equal(a.false_val, b.false_val)
        )
    if isinstance(a, SymCall):
        return a.func_name == b.func_name and len(a.args) == len(b.args) and all(
            _expr_structurally_equal(x, y) for x, y in zip(a.args, b.args)
        )
    return False


def _eval_op(op: str, vals: tp.Sequence[tp.Any]):
    if op == "add":
        return vals[0] + vals[1]
    if op == "sub":
        return vals[0] - vals[1]
    if op == "mul":
        return vals[0] * vals[1]
    if op == "truediv":
        return vals[0] / vals[1]
    if op == "floordiv":
        return vals[0] // vals[1]
    if op == "pow":
        return vals[0] ** vals[1]
    if op == "lshift":
        return vals[0] << vals[1]
    if op == "rshift":
        return vals[0] >> vals[1]
    if op == "and_bits":
        return vals[0] & vals[1]
    if op == "or_bits":
        return vals[0] | vals[1]
    if op == "xor_bits":
        return vals[0] ^ vals[1]
    if op == "invert":
        return ~vals[0]
    if op == "neg":
        return -vals[0]
    raise ValueError(f"Unknown op {op}")


def _eval_cmp(op: str, left, right):
    if op == "lt":
        return left < right
    if op == "le":
        return left <= right
    if op == "gt":
        return left > right
    if op == "ge":
        return left >= right
    raise ValueError(f"Unknown comparison {op}")


FUNCTIONS_SIMPLE = {
    "abs": abs,
    "round": round,
    "int": int,
    "float": float,
    "max": max,
    "min": min,
}

_FUNCTION_REGISTRY = FUNCTIONS_SIMPLE.copy()


########## Spec interpreter ##########


class _SpecEvaluator(ast.NodeVisitor):
    def __init__(self, func):
        self.func = func
        source = textwrap.dedent(inspect.getsource(func))
        self.module = ast.parse(source)
        self.globals = func.__globals__
        self.closure = {}
        if func.__closure__:
            freevars = func.__code__.co_freevars
            for name, cell in zip(freevars, func.__closure__):
                self.closure[name] = cell.cell_contents
        self.env: dict[str, SymBase] = {}
        self.return_value: tp.Optional[SymBase] = None

    def run(self, arg_map: dict[str, SymBase]) -> SymBase:
        self.env = arg_map.copy()
        for stmt in self.module.body:
            if isinstance(stmt, ast.FunctionDef):
                for inner in stmt.body:
                    self.visit(inner)
                break
        assert self.return_value is not None, "Spec function missing return"
        return self.return_value

    def visit_Return(self, node: ast.Return):
        self.return_value = self._eval_expr(node.value)

    def visit_Assign(self, node: ast.Assign):
        value = self._eval_expr(node.value)
        for target in node.targets:
            if isinstance(target, ast.Name):
                self.env[target.id] = value
            else:
                raise NotImplementedError(f"Unsupported assignment target: {ast.dump(target)}")

    def visit_If(self, node: ast.If):
        test = self._eval_expr(node.test)
        test_simplified = to_sym_bool(test).simplify()
        if isinstance(test_simplified, SymBoolConst):
            branch = node.body if test_simplified.value else node.orelse
            for stmt in branch:
                self.visit(stmt)
        else:
            raise NotImplementedError("Symbolic branch conditions are not supported yet")

    def generic_visit(self, node):
        raise NotImplementedError(f"Unsupported AST node: {ast.dump(node)}")

    def _eval_expr(self, node: ast.AST) -> SymBase:
        if isinstance(node, ast.Constant):
            return SymConst(node.value)
        if isinstance(node, ast.Name):
            if node.id in self.env:
                return self.env[node.id]
            if node.id in self.closure:
                return to_sym(self.closure[node.id])
            if node.id in self.globals:
                return to_sym(self.globals[node.id])
            if node.id in _FUNCTION_REGISTRY:
                return SymConst(_FUNCTION_REGISTRY[node.id])
            raise NameError(f"Unknown identifier {node.id} in spec")
        if isinstance(node, ast.BinOp):
            left = self._eval_expr(node.left)
            right = self._eval_expr(node.right)
            op_type = type(node.op)
            if op_type is ast.Add:
                return left + right
            if op_type is ast.Sub:
                return left - right
            if op_type is ast.Mult:
                return left * right
            if op_type is ast.Div:
                return left / right
            if op_type is ast.FloorDiv:
                return left.__floordiv__(right)
            if op_type is ast.Pow:
                return left ** right
            if op_type is ast.LShift:
                return left << right
            if op_type is ast.RShift:
                return left >> right
            if op_type is ast.BitOr:
                return left.__or__(right)
            if op_type is ast.BitXor:
                return left.__xor__(right)
            if op_type is ast.BitAnd:
                return left.__and__(right)
            raise NotImplementedError(f"Unsupported BinOp {op_type}")
        if isinstance(node, ast.UnaryOp):
            operand = self._eval_expr(node.operand)
            if isinstance(node.op, ast.USub):
                return -operand
            if isinstance(node.op, ast.Invert):
                return ~operand
            if isinstance(node.op, ast.Not):
                return SymNot(operand)
            if isinstance(node.op, ast.UAdd):
                return operand
            raise NotImplementedError(f"Unsupported UnaryOp {type(node.op)}")
        if isinstance(node, ast.BoolOp):
            vals = [to_sym_bool(self._eval_expr(v)) for v in node.values]
            if isinstance(node.op, ast.And):
                return SymBoolOp("and", vals)
            if isinstance(node.op, ast.Or):
                return SymBoolOp("or", vals)
            raise NotImplementedError(f"Unsupported BoolOp {type(node.op)}")
        if isinstance(node, ast.Compare):
            left = self._eval_expr(node.left)
            assert len(node.comparators) == 1, "Chained comparisons unsupported"
            right = self._eval_expr(node.comparators[0])
            op = node.ops[0]
            if isinstance(op, ast.Eq):
                return SymEq(left, right)
            if isinstance(op, ast.NotEq):
                return SymNot(SymEq(left, right))
            if isinstance(op, ast.Lt):
                return SymCmp("lt", left, right)
            if isinstance(op, ast.LtE):
                return SymCmp("le", left, right)
            if isinstance(op, ast.Gt):
                return SymCmp("gt", left, right)
            if isinstance(op, ast.GtE):
                return SymCmp("ge", left, right)
            raise NotImplementedError(f"Unsupported comparator {type(op)}")
        if isinstance(node, ast.IfExp):
            cond = self._eval_expr(node.test)
            body = self._eval_expr(node.body)
            orelse = self._eval_expr(node.orelse)
            return SymIf(cond, body, orelse)
        if isinstance(node, ast.Call):
            func_expr = self._eval_expr(node.func)
            args = [self._eval_expr(a) for a in node.args]
            if isinstance(func_expr, SymConst) and callable(func_expr.value):
                func = func_expr.value
                name = getattr(func, "__name__", str(func))
                return SymCall(name, args)
            if isinstance(node.func, ast.Attribute):
                attr_name = node.func.attr
                return SymCall(attr_name, args)
            raise NotImplementedError("Unsupported call target")
        if isinstance(node, ast.Subscript):
            base = self._eval_expr(node.value)
            idx_node = node.slice
            if isinstance(idx_node, ast.Constant):
                idx = idx_node.value
            elif isinstance(idx_node, ast.Index) and isinstance(idx_node.value, ast.Constant):  # type: ignore[attr-defined]
                idx = idx_node.value.value
            else:
                idx = self._eval_expr(idx_node)
            if isinstance(idx, SymConst):
                idx = idx.value
            return SymIndex(base, idx)
        if isinstance(node, ast.Tuple):
            return SymTuple([self._eval_expr(elt) for elt in node.elts])
        raise NotImplementedError(f"Unsupported expression {ast.dump(node)}")


########## Verification helpers ##########


def _solve_out_expression(spec_expr: SymBase, out_sym: SymVar) -> tp.Optional[SymBase]:
    expr = spec_expr.simplify()
    # Direct equality case
    if isinstance(expr, SymEq):
        left_contains = expr.left.contains(out_sym)
        right_contains = expr.right.contains(out_sym)
        if left_contains and not right_contains:
            if _expr_structurally_equal(expr.left, out_sym):
                return expr.right
        if right_contains and not left_contains:
            if _expr_structurally_equal(expr.right, out_sym):
                return expr.left
    # Conjunction of element-wise equalities for tuple outputs
    if isinstance(expr, SymBoolOp) and expr.op == "and":
        assignments = {}
        for part in expr.args:
            part = part.simplify()
            if isinstance(part, SymEq):
                left, right = part.left, part.right
                if isinstance(left, SymIndex) and left.base.contains(out_sym) and not right.contains(out_sym):
                    assignments[left.idx] = right
                elif isinstance(right, SymIndex) and right.base.contains(out_sym) and not left.contains(out_sym):
                    assignments[right.idx] = left
        if assignments:
            max_idx = max(assignments.keys())
            items = []
            for idx in range(max_idx + 1):
                if idx not in assignments:
                    return None
                items.append(assignments[idx])
            return SymTuple(items)
    return None


def _eval_spec(func, arg_values: list[SymBase], out_value: SymBase) -> SymBase:
    sig = inspect.signature(func)
    param_names = list(sig.parameters.keys())
    assert len(param_names) == len(arg_values) + 1, "Spec must have args + out"
    env = {name: val for name, val in zip(param_names[:-1], arg_values)}
    env[param_names[-1]] = out_value
    evaluator = _SpecEvaluator(func)
    return evaluator.run(env)


def _symbolic_value(node: Node, cache: dict[Node, SymBase]) -> SymBase:
    if node in cache:
        return cache[node]

    if isinstance(node, Var):
        sym = SymVar(node.name, typ=node.node_type)
        cache[node] = sym
        return sym
    if isinstance(node, Const):
        const_val = to_sym(node.val.to_spec())
        cache[node] = const_val
        return const_val
    if isinstance(node, (Primitive, Composite)):
        arg_exprs = [_symbolic_value(arg, cache) for arg in node.args]
        out_sym = SymVar(node.name, typ=node.node_type)
        spec_expr = _eval_spec(node.spec, arg_exprs, out_sym)
        solved = _solve_out_expression(spec_expr, out_sym)
        if solved is None:
            raise NotImplementedError(f"Cannot solve spec for node {node.name}: {spec_expr}")
        result = solved.simplify()
        cache[node] = result
        return result
    if isinstance(node, Op):
        arg_exprs = [_symbolic_value(arg, cache) for arg in node.args]
        result = SymCall(node.name, arg_exprs).simplify()
        cache[node] = result
        return result
    raise NotImplementedError(f"Symbolic evaluation not implemented for {type(node)}")


def verify_composite_spec(design: Composite) -> SymBase:
    """Returns the simplified symbolic result of design.spec when fed with the implementation output.

    If the result is Bool(True), the composite spec matches the chain of primitive specs.
    """
    cache: dict[Node, SymBase] = {}
    arg_exprs = [_symbolic_value(arg, cache) for arg in design.args]
    impl_root = design.printing_helper(*design.args)
    impl_out = _symbolic_value(impl_root, cache)
    spec_expr = _eval_spec(design.spec, arg_exprs, impl_out)
    return spec_expr.simplify()
