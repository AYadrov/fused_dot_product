from cvc5.pythonic import Solver, unsat, sat, unknown, If, IntVal, ToReal, Int2BV, Extract, BV2Int


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
