// ASTDumpers.cpp
#include <TensorForge/Frontend/AST.h>
#include <cstdint>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace tensorforge;

void TFProgram::dump(uint8_t Indent) const {
  for (const auto &F : FunctionDefs) {
    F->dump(Indent);
  }
}

void TFFunctionDef::dump(uint8_t Indent) const {
  outs() << "Function Def: " << Name;
}

void TFParameter::dump(uint8_t Indent) const {}
