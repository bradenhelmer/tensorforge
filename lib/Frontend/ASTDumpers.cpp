// ASTDumpers.cpp
#include <TensorForge/Frontend/AST.h>
#include <TensorForge/Frontend/Typing.h>
#include <cstdint>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace tensorforge;

/* Core */

void TFProgram::dump(uint8_t Indent) const {
  for (const auto &F : FunctionDefs) {
    F->dump(Indent);
  }
}

void TFTypeNode::dump(uint8_t Indent) const {}

/* Function */

void TFFunctionDef::dump(uint8_t Indent) const {
  outs() << "Function Def: " << Name;
}

void TFParameter::dump(uint8_t Indent) const {}

void TFReturnStatement::dump(uint8_t Indent) const {}
