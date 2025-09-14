# RUN: tensorforge --dump-tokens %s | FileCheck %s
a + b - c * d / e % f @ g
x == y != z < w <= v > u >= t
result = value
a += b -= c *= d /= e @= f
array[index], obj.field: function() -> tensor

# CHECK: id
# CHECK: plus
# CHECK: id
# CHECK: minus
# CHECK: id
# CHECK: star
# CHECK: id
# CHECK: slash
# CHECK: id
# CHECK: percent
# CHECK: id
# CHECK: at
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: eqeq
# CHECK: id
# CHECK: ne
# CHECK: id
# CHECK: lt
# CHECK: id
# CHECK: le
# CHECK: id
# CHECK: gt
# CHECK: id
# CHECK: ge
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: eq
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: pluseq
# CHECK: id
# CHECK: minuseq
# CHECK: id
# CHECK: stareq
# CHECK: id
# CHECK: slasheq
# CHECK: id
# CHECK: ateq
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: lbracket
# CHECK: id
# CHECK: rbracket
# CHECK: comma
# CHECK: id
# CHECK: dot
# CHECK: id
# CHECK: plus
# CHECK: id
# CHECK: lparen
# CHECK: rparen
# CHECK: arrow
# CHECK: kw_tensor
# CHECK: newline
# CHECK: eof
