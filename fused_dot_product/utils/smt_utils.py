from cvc5.pythonic import (
    Solver,
    unsat,
    sat,
    unknown,
    If,
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


_POW = Function("pow", RealSort(), IntSort(), RealSort())
_POW_AXIOMS_ATTACHED: set[int] = set()


def _attach_pow_axioms(solver):
    solver_id = id(solver)
    if solver_id in _POW_AXIOMS_ATTACHED:
        return

    x = FreshConst(RealSort())
    y = FreshConst(IntSort())
    c = FreshConst(IntSort())

    solver.add(ForAll([x], _POW(x, IntVal(0)) == RealVal("1")))
    solver.add(ForAll([x], _POW(x, IntVal(1)) == x))
    solver.add(ForAll([x, y, c], _POW(x, y + c) == _POW(x, y) * _POW(x, c)))
    # solver.add(ForAll([x, y, c], _POW(x, y - c) == _POW(x, y) / _POW(x, c)))
    # solver.add(ForAll([x, y], _POW(IntVal(2), y) == pow2_int(y, 512)))

    _POW_AXIOMS_ATTACHED.add(solver_id)


def pow_(base, exponent, solver=None):
    base_real = base
    if hasattr(base, "is_int") and base.is_int():
        base_real = ToReal(base)
    elif not hasattr(base, "is_real"):
        if isinstance(base, int):
            base_real = ToReal(IntVal(base))
        else:
            base_real = RealVal(str(base))

    exp_int = exponent
    if hasattr(exponent, "is_real") and exponent.is_real():
        exp_int = ToInt(exponent)
    elif not hasattr(exponent, "is_int"):
        exp_int = IntVal(int(exponent))

    if solver is not None:
        _attach_pow_axioms(solver)

    return _POW(base_real, exp_int)


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

def _unroller(query1, query2, s):
    if isinstance(query1, tuple) and isinstance(query2, tuple):
        for q1, q2 in zip(query1, query2):
            _unroller(q1, q2, s)
    elif isinstance(query1, list) and isinstance(query2, list):
        for q1, q2 in zip(query1, query2):
            _unroller(q1, q2, s)
    else:
        s.add(query1 != query2)
    return None


def cvc5_prove_equal(query1, query2, solver):
    _unroller(query1, query2, solver)
    
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
