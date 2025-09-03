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

  /* Core lexical functions */
  bool lexFloatOrIntLiteral(TFToken *Out);
  bool lexId(TFToken *Out);
  bool lexIndent(TFToken *Out);
  bool lexNewline(TFToken *Out);
  bool lexToken(TFToken *Out);
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_LEXER_H */
