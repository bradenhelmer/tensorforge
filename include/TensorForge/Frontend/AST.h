// AST.h
#ifndef TF_FRONTEND_AST_H
#define TF_FRONTEND_AST_H

#include "TensorForge/Frontend/Token.h"
#include <memory>
#include <optional>
#include <vector>
namespace tensorforge {

class TFFunctionDef;
class TFParameter;

class TFASTNode {};

class TFProgram : public TFASTNode {
private:
  std::vector<std::unique_ptr<TFFunctionDef>> FunctionDefs;

public:
  TFProgram() = default;

  void addFunction(std::unique_ptr<TFFunctionDef> Function) {
    FunctionDefs.push_back(Function);
  }
};

class TFFunctionDef : public TFASTNode {
private:
  std::vector<std::unique_ptr<TFParameter>> Parameters;
};

class TFParameter : public TFASTNode {
private:
  llvm::StringRef Name;
  std::optional<TFTokenKind> Type;

public:
  TFParameter(llvm::StringRef Name) : Name(Name) {}
  TFParameter(llvm::StringRef Name, TFTokenKind Type)
      : Name(Name), Type(Type) {}
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_AST_H */
