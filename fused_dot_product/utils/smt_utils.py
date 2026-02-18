from cvc5.pythonic import (
    Solver,
    unsat,
    sat,
    unknown,
    If,
    Or,
    And,
    BoolVal,
    Function,
    ForAll,
    FreshConst,
    RealSort,
    IntSort,
    IntVal,
    RealVal,
    ToInt,
    ToReal,
    Int2BV,
    Extract,
    BV2Int,
)


_POW = Function("pow", RealSort(), RealSort(), RealSort())
_POW_AXIOMS_ATTACHED: set[int] = set()


def _attach_pow_axioms(solver):
    solver_id = id(solver)
    if solver_id in _POW_AXIOMS_ATTACHED:
        return

    x = FreshConst(RealSort())
    y = FreshConst(RealSort())
    c = FreshConst(RealSort())

    solver.add(ForAll([x], _POW(x, RealVal(0)) == RealVal("1")))
    solver.add(ForAll([x], _POW(x, RealVal(1)) == x))
    solver.add(ForAll([x, y, c], _POW(x, y + c) == _POW(x, y) * _POW(x, c)))
    solver.add(ForAll([x, y, c], _POW(x, y - c) == _POW(x, y) / _POW(x, c)))

    _POW_AXIOMS_ATTACHED.add(solver_id)


def pow_(base, exponent, solver=None):
    if solver is not None:
        _attach_pow_axioms(solver)
    return _POW(base, exponent)


def pow2(base, shift_int, max_abs_shift: int):
    # Encode base * 2**shift_int without symbolic POW.
    bit_count = max_abs_shift.bit_length()
    if bit_count == 0:
        return base

    pos_shift = If(shift_int >= 0, shift_int, IntVal(0))
    neg_shift = If(shift_int < 0, -shift_int, IntVal(0))
    pos_shift_bv = Int2BV(pos_shift, bit_count)
    neg_shift_bv = Int2BV(neg_shift, bit_count)

    scaled = base
    for bit in range(bit_count):
        factor = ToReal(IntVal(1 << (1 << bit)))
        pos_bit = BV2Int(Extract(bit, bit, pos_shift_bv))
        neg_bit = BV2Int(Extract(bit, bit, neg_shift_bv))
        scaled = If(pos_bit == 1, scaled * factor, scaled)
        scaled = If(neg_bit == 1, scaled / factor, scaled)
    return scaled


def pow2_int(shift, max_abs_shift: int = 256):

    shift_int = shift
    if hasattr(shift, "is_real") and shift.is_real():
        shift_int = ToInt(shift)
    elif not hasattr(shift, "is_int"):
        shift_int = IntVal(int(shift))

    bit_count = max_abs_shift.bit_length()
    if bit_count == 0:
        return IntVal(1)

    shift_nonneg = If(shift_int >= 0, shift_int, IntVal(0))
    shift_bv = Int2BV(shift_nonneg, bit_count)

    out = IntVal(1)
    for bit in range(bit_count):
        factor = IntVal(1 << (1 << bit))
        bit_is_set = BV2Int(Extract(bit, bit, shift_bv))
        out = If(bit_is_set == 1, out * factor, out)
    return out

def _unroller(query1, query2):
    if isinstance(query1, tuple) and isinstance(query2, tuple):
        assert len(query1) == len(query2), "Tuple lengths must match"
        clauses = []
        for q1, q2 in zip(query1, query2):
            clauses.extend(_unroller(q1, q2))
        return clauses
    elif isinstance(query1, list) and isinstance(query2, list):
        assert len(query1) == len(query2), "List lengths must match"
        clauses = []
        for q1, q2 in zip(query1, query2):
            clauses.extend(_unroller(q1, q2))
        return clauses
    else:
        return [query1 != query2]


def cvc5_prove_equal(query1, query2, solver):
    constraints = _unroller(query1, query2)
    
    for c in constraints:
        solver.add(c)
        
        print(solver.sexpr())
        
        res = solver.check()
        print(res)
        
        if res == unsat:
            print("proved")
        elif res == unknown:
            print(solver.reason_unknown())
        else:
            model = solver.model()
            print("failed to prove")
        print(f"Counterexample found:\n{model}")

