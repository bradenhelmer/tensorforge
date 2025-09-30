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

  /* Type Registry */
  std::unique_ptr<TypeRegistry> Registry;

public:
  TFParser(llvm::StringRef Buffer) : Lexer(std::make_unique<TFLexer>(Buffer)) {}

  /* Utility methods */
  void advance() { Lexer->lexToken(&CurrToken); }
  void dumpTokens();

  /* Matchers */
  void hardMatch(TFTokenKind Kind);

  inline void hardMatchConsume(TFTokenKind Kind) {
    hardMatch(Kind);
    advance();
  }
  inline void advanceHardMatch(TFTokenKind Kind) {
    advance();
    hardMatch(Kind);
  }

  inline void advanceHardMatchConsume(TFTokenKind Kind) {
    advanceHardMatch(Kind);
    advance();
  }

  inline void advanceSoftMatch(TFTokenKind Kind) {
    if (CurrToken.Kind == Kind) {
      advance();
    }
  }

  /* Core parsing methods */
  std::unique_ptr<TFProgram> parseTFProgram();

  /* Type Parsing */
  TFType *parseTFType();
  TensorType *parseTensorType();

  /* Function Parsing */
  std::unique_ptr<TFFunctionDef> parseTFFunctionDef();
  std::unique_ptr<TFParameter> parseTFParameter();

  /* Statement Parsing */
  std::unique_ptr<TFStatement> parseTFStatement();
  std::unique_ptr<TFReturnStatement> parseTFReturnStatement();

  /* Expression Parsing */
  std::unique_ptr<TFExpression> parseTFExpression();
  std::unique_ptr<TFIntegerLiteralExpression> parseTFIntegerLiteralExpression();
};
} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_PARSER_H */
