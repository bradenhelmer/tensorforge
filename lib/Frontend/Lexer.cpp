// Lexer.cpp
#include "TensorForge/Frontend/Lexer.h"
#include "TensorForge/Frontend/Token.h"

using namespace tensorforge;

bool TFLexer::lexFloatOrIntLiteral(TFToken *Out) {}

bool TFLexer::lexId(TFToken *Out) {
  do {
    BufferPtr++;
  } while (isIdentifierChar(*BufferPtr));
  Out->End = BufferPtr - 1;
  Out->Kind = getPossibleKWFromID(Out->getTokenString());
  return true;
}

bool TFLexer::lexIndent(TFToken *Out) {
  uint8_t NewLevel;
  uint8_t Spaces = 0;

  while (*(++BufferPtr) == ' ') {
    Spaces++;
    CurrLoc.Col++;
  }

  if (Spaces % 4 != 0) {
    Out->Kind = invalid;
    return false;
  }

  NewLevel = Spaces / 4;
  if (NewLevel > CurrIndentLevel) {
    CurrIndentLevel = NewLevel;
    Out->Kind = indent;
  } else if (NewLevel < CurrIndentLevel) {
    CurrIndentLevel = NewLevel;
    Out->Kind = dedent;
  }
  return true;
}

bool TFLexer::lexNewline(TFToken *Out) {
  while (*(++BufferPtr) == '\n') {
    CurrLoc.Line++;
    CurrLoc.Col = 1;
  }
  Out->Kind = newline;
  return true;
}

bool TFLexer::lexToken(TFToken *Out) {
  if (*BufferPtr == '\n') {
    return lexNewline(Out);
  }

  Out->Start = BufferPtr;
  Out->End = BufferPtr;

  if (Out->Kind == newline) {
    return lexIndent(Out);
  }

  const char Peek = *(BufferPtr + 1);

  switch (*BufferPtr) {
  case 0:
    Out->Kind = eof;
    return true;
  case '%':
    Out->Kind = percent;
    break;
  case ',':
    Out->Kind = comma;
    break;
  case '.':
    Out->Kind = dot;
    break;
  case '[':
    Out->Kind = lbracket;
    break;
  case ']':
    Out->Kind = rbracket;
    break;
  case '(':
    Out->Kind = lparen;
    break;
  case ')':
    Out->Kind = rparen;
    break;
  case '+':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = pluseq;
      break;
    }
    Out->Kind = plus;
    break;
  case '-':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = minuseq;
      break;
    }
    if (Peek == '>') {
      Out->End = ++BufferPtr;
      Out->Kind = arrow;
      break;
    }
    Out->Kind = minus;
    break;
  case '*':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = stareq;
      break;
    }
    Out->Kind = star;
    break;
  case '/':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = slasheq;
      break;
    }
    Out->Kind = slash;
    break;
  case '@':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = ateq;
      break;
    }
    Out->Kind = at;
    break;
  case '=':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = eqeq;
      break;
    }
    Out->Kind = eq;
    break;
  case '>':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = ge;
      break;
    }
    Out->Kind = gt;
    break;
  case '<':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = le;
      break;
    }
    Out->Kind = lt;
    break;
  case '!':
    if (Peek == '=') {
      Out->End = ++BufferPtr;
      Out->Kind = ne;
      break;
    }
    return false;
    // clang-format off
  case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
  case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
  case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
  case 'V': case 'W': case 'X': case 'Y': case 'Z':
  case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
  case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
  case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
  case 'v': case 'w': case 'x': case 'y': case 'z':
  case '_':
    Out->Kind = id;
    return lexId(Out);
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    // clang-format on
    return lexFloatOrIntLiteral(Out);
  }
  BufferPtr++;
  return true;
}
