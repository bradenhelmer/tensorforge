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
  return Program;
}

std::unique_ptr<TFFunctionDef> TFParser::parseTFFunctionDef() {

  // Parse def and id.
  hardMatchConsume(kw_def);
  hardMatch(id);
  StringRef FuncName(CurrToken.getTokenString());
  advanceHardMatchConsume(lparen);

  // Parse function parameters.
  std::vector<std::unique_ptr<TFParameter>> Parameters;
  while (CurrToken.Kind != rparen) {
    Parameters.push_back(parseTFParameter());
    advanceSoftMatch(comma);
  }

  // Parse return type.
  advanceHardMatchConsume(arrow);
  TFType *FuncRetType = parseTFType();
  hardMatchConsume(colon);
  hardMatchConsume(indent);

  // Parse Statements
  std::vector<std::unique_ptr<TFStatement>> Statements;
  while (CurrToken.Kind != dedent) {
    Statements.push_back(parseTFStatement());
  }
  return std::make_unique<TFFunctionDef>(FuncName, std::move(Parameters),
                                         FuncRetType);
}

std::unique_ptr<TFParameter> TFParser::parseTFParameter() {
  advanceHardMatch(id);
  StringRef ParamName = CurrToken.getTokenString();
  advanceHardMatchConsume(colon);
  TFType *Type = parseTFType();
  return std::make_unique<TFParameter>(ParamName, Type);
}

TFType *TFParser::parseTFType() {
  TFType *ParsedType;
  switch (CurrToken.Kind) {
  case kw_int32:
    ParsedType = Registry->getScalarType(ScalarType::DType::Int32);
  case kw_int64:
    ParsedType = Registry->getScalarType(ScalarType::DType::Int64);
  case kw_float16:
    ParsedType = Registry->getScalarType(ScalarType::DType::Float16);
  case kw_float32:
    ParsedType = Registry->getScalarType(ScalarType::DType::Float32);
  case kw_float64:
    ParsedType = Registry->getScalarType(ScalarType::DType::Float64);
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

TensorType *TFParser::parseTensorType() {}

std::unique_ptr<TFStatement> TFParser::parseTFStatement() {
  switch (CurrToken.Kind) {
  case kw_return:
    return parseTFReturnStatement();
  default:
    errs() << "Error parsing statement\n";
  }
}

std::unique_ptr<TFReturnStatement> TFParser::parseTFReturnStatement() {
  hardMatchConsume(kw_return);
  return std::make_unique<TFReturnStatement>(parseTFExpression());
}

std::unique_ptr<TFExpression> TFParser::parseTFExpression() {}
