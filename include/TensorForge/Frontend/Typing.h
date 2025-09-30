// Typing.h

#ifndef TF_FRONTEND_TYPING_H
#define TF_FRONTEND_TYPING_H

#include <cstdint>
#include <llvm/ADT/SmallVector.h>

namespace tensorforge {

class TFType {
public:
  enum class Kind { Scalar, Tensor };
  virtual void dump(uint8_t Indent = 0) const = 0;
  virtual bool equals(const TFType *Other) const = 0;
  virtual ~TFType() = default;

private:
  Kind TypeKind;

public:
  Kind getKind() const { return TypeKind; }
  TFType(Kind TypeKind) : TypeKind(TypeKind) {}
};

class ScalarType : public TFType {
public:
  enum class DType { Int32, Int64, Float16, Float32, Float64 };

  explicit ScalarType(DType DTypeStorage)
      : TFType(Kind::Scalar), DTypeStorage(DTypeStorage) {}

  void dump(uint8_t Indent = 0) const override;
  bool equals(const TFType *Other) const override;

  static bool classof(const TFType *T) { return T->getKind() == Kind::Scalar; }

private:
  DType DTypeStorage;
};

class TensorType : public TFType {
  ScalarType ElemType;
  llvm::SmallVector<uint64_t> Dims;

public:
  TensorType(ScalarType ElemType, llvm::SmallVector<uint64_t> Dims)
      : TFType(Kind::Tensor), ElemType(ElemType), Dims(std::move(Dims)) {}
  void dump(uint8_t Indent = 0) const override;
  bool equals(const TFType *Other) const override;
};

class TypeRegistry {
  std::unordered_map<ScalarType::DType, std::unique_ptr<ScalarType>>
      ScalarTypes;
  std::vector<std::unique_ptr<TensorType>> TensorTypes;

public:
  TypeRegistry();

  ScalarType *getScalarType(ScalarType::DType DType);
  TensorType *getTensorType(ScalarType::DType DType,
                            llvm::SmallVector<uint64_t> Dims);
};

} // namespace tensorforge

#endif /* ifndef TF_FRONTEND_TYPING_H */
