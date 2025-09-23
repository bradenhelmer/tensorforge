# RUN: tensorforge --dump-tokens %s | FileCheck %s
42
123456
0
3.14159
0.5
42.0
identifier
_private
CamelCase
snake_case

# CHECK: int_lit
# CHECK: newline
# CHECK: int_lit
# CHECK: newline
# CHECK: int_lit
# CHECK: newline
# CHECK: float_lit
# CHECK: newline
# CHECK: float_lit
# CHECK: newline
# CHECK: float_lit
# CHECK: newline
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: newline
# CHECK: id
# CHECK: newline
# CHECK: eof