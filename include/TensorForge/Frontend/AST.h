// AST.h
#ifndef TF_FRONTEND_AST_H
#define TF_FRONTEND_AST_H

#include "TensorForge/Frontend/Typing.h"
#include <llvm/ADT/StringRef.h>
#include <memory>
#include <vector>
namespace tensorforge {

class TFFunctionDef;
class TFParameter;

class TFASTNode {
public:
  virtual ~TFASTNode() = default;
  virtual void dump(uint8_t Indent = 0) const = 0;
};

class TFProgram : public TFASTNode {
private:
  std::vector<std::unique_ptr<TFFunctionDef>> FunctionDefs;

public:
  TFProgram() = default;

  void dump(uint8_t Indent = 0) const override;

  void addFunction(std::unique_ptr<TFFunctionDef> Function) {
    FunctionDefs.push_back(std::move(Function));
  }
};

class TFFunctionDef : public TFASTNode {
private:
  std::string Name;
  std::vector<std::unique_ptr<TFParameter>> Parameters;

public:
  TFFunctionDef(llvm::StringRef Name) : Name(Name) {}

  void dump(uint8_t Indent = 0) const override;

  void addParameter(std::unique_ptr<TFParameter> Param) {
    Parameters.push_back(std::move(Param));
  }
};

class TFParameter : public TFASTNode {
private:
  std::string Name;
  TFType Type;

public:
  TFParameter(llvm::StringRef Name, TFType Type) : Name(Name), Type(Type) {}

  void dump(uint8_t Indent = 0) const override;
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_AST_H */
