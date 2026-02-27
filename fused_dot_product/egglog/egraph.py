from egglog import *
from .rules import load_rules

def create_egraph() -> EGraph:
    egraph = EGraph()
    load_rules(egraph)
    return egraph

def egglog_check_eq(expr1, expr2, asserts=[], iterations=6):
    egraph = create_egraph()
    
    for assert_ in asserts:
        egraph.register(assert_)
    
    egraph.register(expr1)
    egraph.register(expr2)
    
    egraph.run(iterations)
    
    try:
        egraph.check(eq(expr1).to(expr2))
        print(f"verified")
        return True
    except EggSmolError:
        print(f"not verified")
        print(egraph.extract(expr1))
        print(egraph.extract(expr2))
        return False
