// Parser.cpp
#include "TensorForge/Frontend/Parser.h"
#include "TensorForge/Frontend/Token.h"
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

std::unique_ptr<TFProgram> TFParser::parseTFProgram() {
  return std::make_unique<TFProgram>();
}
