// tensorforge.cpp
#include "TensorForge/Frontend/Parser.h"
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace tensorforge;

// Command Line Options

static cl::opt<std::string> inputFilename(cl::Positional,
                                          cl::desc("<input tensorforge file>"),
                                          cl::Required);

static cl::opt<std::string> outputFilename("o", cl::desc("Output filename"),
                                           cl::value_desc("filename"),
                                           cl::init("-"));

static cl::opt<bool> dumpTokens("dump-tokens",
                                cl::desc("Dump tokens for source file."),
                                cl::init(false));

static cl::opt<bool> dumpAST("dump-ast", cl::desc("Dump AST for source file."),
                             cl::init(false));

int main(int argc, char *argv[]) {
  InitLLVM X(argc, argv);
  cl::ParseCommandLineOptions(argc, argv, "TensorForge Compiler\n");

  auto FileOrError = MemoryBuffer::getFile(inputFilename);
  if (std::error_code EC = FileOrError.getError()) {
    errs() << EC.message();
    return EC.value();
  }

  std::unique_ptr<MemoryBuffer> InputFile = std::move(*FileOrError);

  TFParser Parser(InputFile->getBuffer());

  if (dumpTokens) {
    Parser.dumpTokens();
    return 0;
  }

  auto program = Parser.parseTFProgram();

  if (dumpAST) {
    program->dump();
  }

  return 0;
}
