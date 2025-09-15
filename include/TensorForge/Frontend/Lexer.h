// Lexer.h
#ifndef TF_FRONTEND_LEXER_H
#define TF_FRONTEND_LEXER_H

#include "TensorForge/Frontend/Token.h"
#include <cctype>
#include <cstdint>
#include <llvm/ADT/StringRef.h>

namespace tensorforge {

struct SourceLocation {
  uint16_t Line = 1;
  uint16_t Col = 1;
};

class TFLexer {

private:
  /* Buffer pointers */
  const char *BufferStart;
  const char *BufferPtr;
  const char *BufferEnd;

  /* Current indentation level */
  uint8_t CurrIndentLevel;

  /* Source location tracking */
  SourceLocation CurrLoc;

public:
  TFLexer(llvm::StringRef Buffer)
      : BufferStart(Buffer.data()), BufferPtr(Buffer.data()),
        BufferEnd(Buffer.data() + Buffer.size()), CurrIndentLevel(0) {}

  /* Utility functions */
  static inline bool isIdentifierChar(char c) {
    return std::isalpha(c) || std::isdigit(c) || c == '_';
  }

  inline uint8_t getLine() const { return CurrLoc.Line; }

  inline uint8_t getCol() const { return CurrLoc.Col; }

  inline void traverseForward() {
    BufferPtr++;
    CurrLoc.Col++;
  }

  /* Core lexical functions */
  void lexComment();
  bool lexFloatOrIntLiteral(TFToken *Out);
  bool lexIdOrKeyword(TFToken *Out);
  bool lexIndent(TFToken *Out);
  bool lexToken(TFToken *Out);
  void lexWhitespace();
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_LEXER_H */
