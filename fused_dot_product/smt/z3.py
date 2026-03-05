from ..spec import SpecContext

import z3

def z3_check(ctx: SpecContext, timeout: int = 10000):
    s = z3.Solver()
    s.set(timeout=timeout)
    
    program = ctx.to_z3()
    s.add(program)
    
    print(s.sexpr())
    
    res = s.check()
    print(res)
    
    if res == z3.unsat:
        print(f"{ctx.name} proved with Z3")
    elif res == z3.unknown:
        print(s.reason_unknown())
    else:
        model = s.model()
        print(f"{ctx.name} failed to prove with Z3")
        print(f"Counterexample found:\n{model}")
