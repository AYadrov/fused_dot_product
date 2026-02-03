from cvc5.pythonic import Solver, unsat, sat, unknown

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
