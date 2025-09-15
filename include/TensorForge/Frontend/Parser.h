// Parser.h
#ifndef TF_FRONTEND_PARSER_H
#define TF_FRONTEND_PARSER_H
#include "TensorForge/Frontend/AST.h"
#include "TensorForge/Frontend/Lexer.h"
#include "TensorForge/Frontend/Token.h"

#include <llvm/ADT/StringRef.h>
#include <memory>
namespace tensorforge {

class TFParser {
private:
  /* Lexical Items */
  TFToken CurrToken;
  std::unique_ptr<TFLexer> Lexer;

public:
  TFParser(llvm::StringRef Buffer) : Lexer(std::make_unique<TFLexer>(Buffer)) {}

  /* Utility methods */
  void advance();
  void dumpTokens();

  /* Matchers */
  void hardMatch(TFTokenKind Kind);

  /* Core parsing methods */
  std::unique_ptr<TFProgram> parseTFProgram();
};
} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_PARSER_H */
