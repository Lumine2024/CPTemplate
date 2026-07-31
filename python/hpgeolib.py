from __future__ import annotations

from decimal import *
from typing import *

ld = Decimal
getcontext().prec = 100
PI: Final = ld(
    "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899"
)
TAU: Final = PI * 2
EPS: Final = ld("1e-40")
ZERO: Final = ld(0)
def sign(x: ld) -> int:
    return 1 if x > EPS else -1 if x < EPS else 0
def cmp(a: ld, b: ld) -> int:
    return sign(a - b)
def comp(x: ld) -> ld:
    x %= TAU
    if x > PI: x -= TAU
    elif x < -PI: x += TAU
    return x

def ldsin(x: ld) -> ld:
    with localcontext() as ctx:
        ctx.prec += 20
        x = comp(x)
        term = x
        result = x
        threshold = ld(1).scaleb(-ctx.prec)
        index = 1
        while abs(term) > threshold:
            term *= -(x * x) / ld((2 * index) * (2 * index + 1))
            result += term
            index += 1
        return +result
def ldcos(x: ld) -> ld:
    with localcontext() as ctx:
        ctx.prec += 20
        x = comp(x)
        term = ld(1)
        result = ld(1)
        threshold = ld(1).scaleb(-ctx.prec)
        index = 1
        while abs(term) > threshold:
            term *= -(x * x) / ld((2 * index - 1) * (2 * index))
            result += term
            index += 1
        return +result
def ldatan(x: ld) -> ld:
    with localcontext() as ctx:
        ctx.prec += 20
        term = x
        result = x
        threshold = ld(1).scaleb(-ctx.prec)
        n = 1
        while abs(term) > threshold:
            term *= -(x * x) * ld(2*n - 1) / ld(2*n + 1)
            result += term
            n += 1
        return +result
def ldatan2(y: ld, x: ld) -> ld:
    with localcontext() as ctx:
        ctx.prec += 10
        if x == 0 and y == 0:
            return ZERO
        if x == 0:
            return PI / 2 * sign(y)
        atan_val = ldatan(abs(y / x))
        if x < 0: atan_val = PI - atan_val
        return comp(atan_val * sign(y))
def ldasin(y: ld) -> ld:
    return ldatan2(y, (1 - y * y).sqrt())
def ldacos(x: ld) -> ld:
    return ldatan2((1 - x * x).sqrt(), x)


