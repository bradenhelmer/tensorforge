# RUN: tensorforge --dump-tokens %s | FileCheck %s
def main():
    a = 1 + 2
    b = 0.1
    return a + 42

# CHECK: kw_def
# CHECK: id
# CHECK: lparen
# CHECK: rparen
# CHECK: plus
# CHECK: indent
# CHECK: id
# CHECK: eq
# CHECK: int_lit
# CHECK: plus
# CHECK: int_lit
# CHECK: newline
# CHECK: id
# CHECK: eq
# CHECK: float_lit
# CHECK: newline
# CHECK: kw_return
# CHECK: id
# CHECK: plus
# CHECK: int_lit
# CHECK: dedent
# CHECK: eof
