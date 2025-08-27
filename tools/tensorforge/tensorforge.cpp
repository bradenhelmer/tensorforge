// tensorforge.cpp
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

// Command Line Options

static cl::opt<std::string> inputFilename(cl::Positional,
                                          cl::desc("<input tensorforge file>"),
                                          cl::Required);

static cl::opt<std::string> outputFilename("o", cl::desc("Output filename"),
                                           cl::value_desc("filename"),
                                           cl::init("-"));

int main(int argc, char *argv[]) {
  InitLLVM X(argc, argv);
  cl::ParseCommandLineOptions(argc, argv, "TensorForge Compiler\n");

  auto FileOrError = MemoryBuffer::getFile(inputFilename);
  if (std::error_code EC = FileOrError.getError()) {
    errs() << EC.message();
    return EC.value();
  }

  std::unique_ptr<MemoryBuffer> InputFile = std::move(*FileOrError);
  return 0;
}
