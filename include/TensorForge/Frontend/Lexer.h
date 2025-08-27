// Lexer.h
#ifndef TF_FRONTEND_LEXER_H
#define TF_FRONTEND_LEXER_H

#include <llvm/ADT/StringRef.h>

namespace tensorforge {

class TFLexer {

private:
  const char *BufferStart;
  const char *BufferPtr;
  const char *BufferEnd;

public:
  TFLexer(llvm::StringRef Buffer)
      : BufferStart(Buffer.data()), BufferPtr(Buffer.data()),
        BufferEnd(Buffer.data() + Buffer.size()) {}
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_LEXER_H */
