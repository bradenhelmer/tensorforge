// Parser.cpp
#include "TensorForge/Frontend/Parser.h"
#include "TensorForge/Frontend/Token.h"
#include <cstdlib>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace tensorforge;

void TFParser::dumpTokens() {
  advance();
  while (CurrToken.Kind != eof) {
    outs() << getTokenName(CurrToken.Kind) << "\n";
    advance();
  }
  outs() << getTokenName(CurrToken.Kind) << "\n";
}

void TFParser::advance() { Lexer->lexToken(&CurrToken); }

void TFParser::hardMatch(TFTokenKind Kind) {
  if (Kind != CurrToken.Kind) {
    errs() << "Expected " << getTokenName(Kind) << ". Got "
           << getTokenName(CurrToken.Kind) << ". Line: " << Lexer->getLine()
           << " Col: " << Lexer->getCol() << "\n";
    std::exit(1);
  }

  errs() << "Expected " << getTokenName(Kind) << ". Got "
         << getTokenName(CurrToken.Kind) << '\n';
}
