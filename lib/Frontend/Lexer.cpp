// Lexer.cpp
#include "TensorForge/Frontend/Lexer.h"
#include "TensorForge/Frontend/Token.h"
#include <cstdlib>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace tensorforge;

void TFLexer::lexComment() {
  do {
    BufferPtr++;
  } while (*BufferPtr != '\n');
  BufferPtr++;
  if (*BufferPtr == '#') {
    lexComment();
  }
}

void TFLexer::lexWhitespace() {
  do {
    BufferPtr++;
  } while (*BufferPtr == ' ');
}

bool TFLexer::lexFloatOrIntLiteral(TFToken *Out) {
  bool DotFound = false;
  do {
    BufferPtr++;
    if (*BufferPtr == '.' && !DotFound) {
      Out->Kind = float_lit;
      BufferPtr++;
      DotFound = true;
    }
  } while (std::isdigit(*BufferPtr));
  Out->End = BufferPtr - 1;
  return true;
}

bool TFLexer::lexIdOrKeyword(TFToken *Out) {
  do {
    BufferPtr++;
  } while (isIdentifierChar(*BufferPtr));
  Out->End = BufferPtr - 1;
  Out->Kind = getPossibleKWFromID(Out->getTokenString());
  return true;
}

bool TFLexer::lexIndent(TFToken *Out) {
  while (*(++BufferPtr) == '\n') {
    CurrLoc.Line++;
    CurrLoc.Col = 1;
  }

  uint8_t NewLevel;
  uint8_t Spaces = 0;

  if (*BufferPtr == ' ') {
    do {
      BufferPtr++;
      Spaces++;
      CurrLoc.Col++;
    } while (*BufferPtr == ' ');
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

bool TFLexer::lexToken(TFToken *Out) {

  if (*BufferPtr == '#') {
    lexComment();
  }

  if (*BufferPtr == ' ') {
    lexWhitespace();
  }

  Out->Start = BufferPtr;
  Out->End = BufferPtr;

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
  case ':':
    Out->Kind = colon;
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
    return lexIdOrKeyword(Out);
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    // clang-format on
    Out->Kind = int_lit;
    return lexFloatOrIntLiteral(Out);
  case '\n':
    Out->Kind = newline;
    return lexIndent(Out);
  }
  BufferPtr++;
  return true;
}
