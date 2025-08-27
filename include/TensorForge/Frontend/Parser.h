// Parser.h
#ifndef TF_FRONTEND_PARSER_H
#define TF_FRONTEND_PARSER_H
#include "TensorForge/Frontend/Lexer.h"
#include "TensorForge/Frontend/Token.h"

#include <llvm/ADT/StringRef.h>
#include <memory>
namespace tensorforge {
class TFParser {
private:
  std::unique_ptr<TFLexer> Lexer;
  TFToken CurrentToken;

public:
  TFParser(llvm::StringRef Buffer) : Lexer(std::make_unique<TFLexer>(Buffer)) {}
};
} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_PARSER_H */
