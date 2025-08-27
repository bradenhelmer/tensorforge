// TokenMacros.h

#ifndef TF_TOKEN
#define TF_TOKEN(X)
#endif /* ifndef TF_TOKEN(X) */

#ifndef TF_OPERATOR
#define TF_OPERATOR(OPERATOR, SYMBOL) TF_TOKEN(OPERATOR)
#endif /* ifndef TF_OPERATOR(OPERATOR, SYMBOL) */

#ifndef TF_KEYWORD
#define TF_KEYWORD(KEYWORD) TF_TOKEN(kw_##KEYWORD)
#endif /* ifndef TF_KEYWORD(KEYWORD) */

// Literals
TF_TOKEN(ID)
TF_TOKEN(INT)
TF_TOKEN(FLOAT)

// Keywords
TF_KEYWORD(def)
TF_KEYWORD(return)
TF_KEYWORD(if)
TF_KEYWORD(else)
TF_KEYWORD(for)
TF_KEYWORD(in)
TF_KEYWORD(and)
TF_KEYWORD(or)
TF_KEYWORD(not)
TF_KEYWORD(tensor)
TF_KEYWORD(float32)
TF_KEYWORD(float16)
TF_KEYWORD(int32)
TF_KEYWORD(int8)

// Arithmetic Operators
TF_OPERATOR(plus, "+")
TF_OPERATOR(minus, "-")
TF_OPERATOR(star, "*")
TF_OPERATOR(slash, "/")
TF_OPERATOR(percent, "%")
TF_OPERATOR(at, "@")

// Comparison Operators
TF_OPERATOR(eqeq, "==")
TF_OPERATOR(ne, "!=")
TF_OPERATOR(lt, "<")
TF_OPERATOR(le, "<=")
TF_OPERATOR(gt, ">")
TF_OPERATOR(ge, ">=")

// Assignment operators
TF_OPERATOR(eq, "=")
TF_OPERATOR(pluseq, "+=")
TF_OPERATOR(minuseq, "-=")
TF_OPERATOR(stareq, "*=")
TF_OPERATOR(slasheq, "/=")
TF_OPERATOR(ateq, "@=")

// Special Operators
TF_OPERATOR(colon, ":")
TF_OPERATOR(arrow, "->")
TF_OPERATOR(comma, ",")
TF_OPERATOR(dot, ".")
TF_OPERATOR(lbracket, "[")
TF_OPERATOR(rbracket, "]")
TF_OPERATOR(lparen, "(")
TF_OPERATOR(rparen, ")")

#undef TF_KEYWORD
#undef TF_OPERATOR
#undef TF_TOKEN
