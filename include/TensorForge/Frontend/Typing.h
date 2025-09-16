// Typing.h

#ifndef TF_FRONTEND_TYPING_H
#define TF_FRONTEND_TYPING_H

#include <cstdint>
#include <llvm/ADT/SmallVector.h>
namespace tensorforge {

class TFType {};

class ScalarType : public TFType {
public:
  enum class DType { Int32, Int64, Float16, Float32, Float64 };

  explicit ScalarType(DType dtype) : dtype(dtype) {}

  DType getKind() const { return dtype; }

private:
  DType dtype;
};

class TensorType : public TFType {
  ScalarType DType;
  llvm::SmallVector<uint64_t> Dims;
};

} // namespace tensorforge

#endif /* ifndef SYMBOL */
