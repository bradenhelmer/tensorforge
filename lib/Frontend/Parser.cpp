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

void TFParser::hardMatch(TFTokenKind Kind) {
  if (Kind != CurrToken.Kind) {
    errs() << "Expected " << getTokenName(Kind) << ". Got "
           << getTokenName(CurrToken.Kind) << ". Line: " << Lexer->getLine()
           << " Col: " << Lexer->getCol() << "\n";
    std::exit(1);
  }
}

std::unique_ptr<TFProgram> TFParser::parseTFProgram() {
  std::unique_ptr<TFProgram> Program;
  advance();
  do {
    Program->addFunction(parseTFFunctionDef());
  } while (CurrToken.Kind != eof);
}

std::unique_ptr<TFFunctionDef> TFParser::parseTFFunctionDef() {
  hardMatchConsume(kw_def);
  hardMatch(id);
  std::unique_ptr<TFFunctionDef> FunctionDef =
      std::make_unique<TFFunctionDef>(CurrToken.getTokenString());
  advanceHardMatchConsume(lparen);
  while (CurrToken.Kind != rparen) {
    FunctionDef->addParameter(parseTFParameter());
    advanceSoftMatch(comma);
  }
  advanceHardMatchConsume(arrow);
  TFType FuncRetType = parseTFType();
}

std::unique_ptr<TFParameter> TFParser::parseTFParameter() {
  advanceHardMatch(id);
  StringRef ParamName = CurrToken.getTokenString();
  advanceHardMatchConsume(colon);
  TFType Type = parseTFType();
  return std::make_unique<TFParameter>(ParamName, Type);
}

TFType TFParser::parseTFType() {
  TFType ParsedType;
  switch (CurrToken.Kind) {
  case kw_int32:
    ParsedType = ScalarType(ScalarType::DType::Int32);
    break;
  case kw_int64:
    ParsedType = ScalarType(ScalarType::DType::Int64);
    break;
  case kw_float16:
    ParsedType = ScalarType(ScalarType::DType::Float16);
    break;
  case kw_float32:
    ParsedType = ScalarType(ScalarType::DType::Float32);
    break;
  case kw_float64:
    ParsedType = ScalarType(ScalarType::DType::Float64);
    break;
  case kw_tensor:
    ParsedType = parseTensorType();
    break;
  default:
    errs() << "Unknown type: " << CurrToken.getTokenString() << '\n';
    std::exit(1);
  }
  advance();
  return ParsedType;
}

TensorType TFParser::parseTensorType() {}
