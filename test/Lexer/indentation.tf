# RUN: tensorforge --dump-tokens %s | FileCheck %s
def example():
    level1 = 1
    if True:
        level2 = 2
        if nested:
            level3 = 3
        back_to_level2 = 4
    back_to_level1 = 5

# CHECK: kw_def
# CHECK: id
# CHECK: lparen
# CHECK: rparen
# CHECK: plus
# CHECK: indent
# CHECK: id
# CHECK: eq
# CHECK: int_lit
# CHECK: newline
# CHECK: kw_if
# CHECK: kw_True
# CHECK: plus
# CHECK: indent
# CHECK: id
# CHECK: eq
# CHECK: int_lit
# CHECK: newline
# CHECK: kw_if
# CHECK: id
# CHECK: plus
# CHECK: indent
# CHECK: id
# CHECK: eq
# CHECK: int_lit
# CHECK: dedent
# CHECK: id
# CHECK: eq
# CHECK: int_lit
# CHECK: dedent
# CHECK: id
# CHECK: eq
# CHECK: int_lit
# CHECK: dedent
# CHECK: eof
