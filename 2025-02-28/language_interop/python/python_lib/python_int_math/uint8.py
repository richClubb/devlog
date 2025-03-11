

UINT8_MAX = 255
UINT8_MIN = 0

INT8_MAX = 127
INT8_MIN = -128


def uint8_add(a, b):
    if ( a + b >= UINT8_MAX ): return UINT8_MAX
    return a + b

def uint8_sub(a, b):
    if (a - b <= UINT8_MIN): return UINT8_MIN
    return a - b