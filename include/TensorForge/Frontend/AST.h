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
class TFExpression;

class TFASTNode {
public:
  virtual ~TFASTNode() = default;
  virtual void dump(uint8_t Indent = 0) const = 0;
};

class TFTypeNode : public TFASTNode {
  TFType *Type;

public:
  TFTypeNode(TFType *Type) : Type(Type) {}
  void dump(uint8_t Indent = 0) const override;
  TFType *getType() const { return Type; }
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
  TFTypeNode RetType;

public:
  TFFunctionDef(llvm::StringRef Name,
                std::vector<std::unique_ptr<TFParameter>> Parameters,
                TFTypeNode RetType)
      : Name(Name), Parameters(std::move(Parameters)), RetType(RetType) {}

  void dump(uint8_t Indent = 0) const override;

  void addParameter(std::unique_ptr<TFParameter> Param) {
    Parameters.push_back(std::move(Param));
  }
};

class TFParameter : public TFASTNode {
private:
  std::string Name;
  TFTypeNode Type;

public:
  TFParameter(llvm::StringRef Name, TFTypeNode Type) : Name(Name), Type(Type) {}

  void dump(uint8_t Indent = 0) const override;
};

class TFStatement : public TFASTNode {};

class TFReturnStatement : public TFStatement {
  std::unique_ptr<TFExpression> Expression;

public:
  TFReturnStatement(std::unique_ptr<TFExpression> Expression)
      : Expression(std::move(Expression)) {}
  void dump(uint8_t Indent = 0) const override;
};

class TFExpression : public TFASTNode {};
class TFIntegerLiteralExpression : public TFExpression {};
class TFFloatLiteralExpression : public TFExpression {};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_AST_H */
