// Typing.cpp

#include <TensorForge/Frontend/Typing.h>
#include <llvm/Support/Casting.h>

using namespace llvm;
using namespace tensorforge;

void ScalarType::dump(uint8_t Indent) const {}
void TensorType::dump(uint8_t Indent) const {}

bool ScalarType::equals(const TFType *Other) const {
  if (auto *OtherScalar = cast<ScalarType>(Other)) {
    return DTypeStorage == OtherScalar->DTypeStorage;
  }
  return false;
}

bool TensorType::equals(const TFType *Other) const {}

TypeRegistry::TypeRegistry() {
  ScalarTypes[ScalarType::DType::Int32] =
      std::make_unique<ScalarType>(ScalarType::DType::Int32);
  ScalarTypes[ScalarType::DType::Int64] =
      std::make_unique<ScalarType>(ScalarType::DType::Int64);
  ScalarTypes[ScalarType::DType::Float16] =
      std::make_unique<ScalarType>(ScalarType::DType::Float16);
  ScalarTypes[ScalarType::DType::Float32] =
      std::make_unique<ScalarType>(ScalarType::DType::Float32);
  ScalarTypes[ScalarType::DType::Float64] =
      std::make_unique<ScalarType>(ScalarType::DType::Float64);
}

ScalarType *TypeRegistry::getScalarType(ScalarType::DType DType) {
  return ScalarTypes[DType].get();
}
