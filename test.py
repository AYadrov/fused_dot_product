import dreal

# Real variables x0..x47 (skip x28, x48 etc. since not used)
xs = {i: dreal.Variable(f"x{i}") for i in range(0, 48)}
x = lambda i: xs[i]

constraints = []


def pow2(expr):
    return dreal.pow(2.0, expr)


# Nonnegativity constraints that appear in the input
for i in [
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 39, 40, 41, 42, 43,
]:
    constraints.append(x(i) >= 0.0)

# Definitions
constraints.append(x(4) == x(0) / 128.0 + 1.0)
constraints.append(x(9) == x(5) / 128.0 + 1.0)
constraints.append(x(10) == x(4) * x(9))

constraints.append(x(19) == x(11) + x(15))
constraints.append(x(20) == x(12) + x(16))
constraints.append(x(21) == dreal.if_then_else(x(19) >= x(20), x(19), x(20)))

constraints.append(x(22) == x(13) + x(17))
constraints.append(x(23) == x(14) + x(18))
constraints.append(x(24) == dreal.if_then_else(x(22) >= x(23), x(22), x(23)))

constraints.append(x(25) == dreal.if_then_else(x(21) >= x(24), x(21), x(24)))
constraints.append(x(26) == x(25) - x(19))

# Normalizations
constraints.append(x(27) == x(10) / pow2(x(26)))

constraints.append(x(29) == x(1) / 128.0 + 1.0)
constraints.append(x(30) == x(6) / 128.0 + 1.0)
constraints.append(x(31) == x(29) * x(30))

constraints.append(x(32) == x(25) - x(20))
constraints.append(x(33) == x(31) / pow2(x(32)))

constraints.append(x(34) == x(2) / 128.0 + 1.0)
constraints.append(x(35) == x(7) / 128.0 + 1.0)
constraints.append(x(36) == x(34) * x(35))

constraints.append(x(37) == x(25) - x(22))
constraints.append(x(38) == x(36) / pow2(x(37)))

constraints.append(x(39) == x(3) / 128.0 + 1.0)
constraints.append(x(40) == x(8) / 128.0 + 1.0)
constraints.append(x(41) == x(39) * x(40))

constraints.append(x(42) == x(25) - x(23))
constraints.append(x(43) == x(41) / pow2(x(42)))

# --- LET blocks translated ---

# Block for x44
let1 = x(11) + x(15)
let2 = x(14) + x(18)
let3 = x(13) + x(17)
let4 = x(12) + x(16)
let5 = dreal.if_then_else(let1 >= let4, let1, let4)
let6 = dreal.if_then_else(let5 >= let3, let5, let3)
max_all = dreal.if_then_else(let6 >= let2, let6, let2)

constraints.append((x(0) / 128.0 + 1.0) * (x(5) / 128.0 + 1.0) == x(44) * pow2(max_all - let1))

# Block for x45
let1b = x(12) + x(16)
let2b = x(14) + x(18)
let3b = x(13) + x(17)
let4b = x(11) + x(15)
let5b = dreal.if_then_else(let4b >= let1b, let4b, let1b)
let6b = dreal.if_then_else(let5b >= let3b, let5b, let3b)
max_all_b = dreal.if_then_else(let6b >= let2b, let6b, let2b)

constraints.append((x(1) / 128.0 + 1.0) * (x(6) / 128.0 + 1.0) == x(45) * pow2(max_all_b - let1b))

# Block for x46
let1c = x(13) + x(17)
let2c = x(14) + x(18)
let3c = x(12) + x(16)
let4c = x(11) + x(15)
let5c = dreal.if_then_else(let4c >= let3c, let4c, let3c)
let6c = dreal.if_then_else(let5c >= let1c, let5c, let1c)
max_all_c = dreal.if_then_else(let6c >= let2c, let6c, let2c)

constraints.append((x(2) / 128.0 + 1.0) * (x(7) / 128.0 + 1.0) == x(46) * pow2(max_all_c - let1c))

# Block for x47
let1d = x(14) + x(18)
let2d = x(13) + x(17)
let3d = x(12) + x(16)
let4d = x(11) + x(15)
let5d = dreal.if_then_else(let4d >= let3d, let4d, let3d)
let6d = dreal.if_then_else(let5d >= let2d, let5d, let2d)
max_all_d = dreal.if_then_else(let6d >= let1d, let6d, let1d)

constraints.append((x(3) / 128.0 + 1.0) * (x(8) / 128.0 + 1.0) == x(47) * pow2(max_all_d - let1d))

# Final OR:
# (or (or (distinct x44 x27) (distinct x45 x33) (distinct x46 x38) (distinct x47 x43))
#     (distinct max_all x25))
eps = 1e-3
constraints.append(
    dreal.Or(
        x(44) - x(27) >= eps,
        x(45) - x(33) >= eps,
        x(46) - x(38) >= eps,
        x(47) - x(43) >= eps,
        max_all - x(25) >= eps,
    )
)

formula = dreal.And(*constraints)
print(formula.to_string())

# Optional check
delta = 1e-14
result = dreal.CheckSatisfiability(formula, delta)
print(f"delta = {delta}")
if result is None:
    print("unsat")
else:
    print("delta-sat")
    print(result)
