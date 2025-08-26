// tensorforge.cpp
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"

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

  return 0;
}
