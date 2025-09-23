# RUN: tensorforge --dump-tokens %s | FileCheck %s
# This is a comment
# Another comment
value # inline comment
# Multi-line
# comment block
42.0
0
123.456

# CHECK: id
# CHECK: newline
# CHECK: float_lit
# CHECK: newline
# CHECK: int_lit
# CHECK: newline
# CHECK: float_lit
# CHECK: newline
# CHECK: eof