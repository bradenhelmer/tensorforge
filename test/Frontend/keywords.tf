# RUN: tensorforge --dump-tokens %s | FileCheck %s
def return if else for in and or not
tensor float32 float16 int32 int8
define returns ifelse forsaken inland android ordinary notation

# CHECK: kw_def
# CHECK: kw_return
# CHECK: kw_if
# CHECK: kw_else
# CHECK: kw_for
# CHECK: kw_in
# CHECK: kw_and
# CHECK: kw_or
# CHECK: kw_not
# CHECK: newline
# CHECK: kw_tensor
# CHECK: kw_float32
# CHECK: kw_float16
# CHECK: kw_int32
# CHECK: kw_int8
# CHECK: newline
# CHECK: id
# CHECK: id
# CHECK: id
# CHECK: id
# CHECK: id
# CHECK: id
# CHECK: id
# CHECK: id
# CHECK: newline
# CHECK: eof
