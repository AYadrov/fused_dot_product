BF16_EXPONENT_BITS = 8
BF16_MANTISSA_BITS = 7
BF16_BIAS = 127
Wf = 30                 # accuracy requirements for intermediate mantissa multiplications
N = 4                   # number of elemenents per vector for dot product operation
SEED = 1760394920
s = 2                   # number of local shift bits for the optimized dot product
SHARED_EXPONENT_BITS = 5
