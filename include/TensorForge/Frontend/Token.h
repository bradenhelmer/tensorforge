// Token.h
#ifndef TF_FRONTEND_TOKEN_H
#define TF_FRONTEND_TOKEN_H

#include <llvm/ADT/StringSwitch.h>

#include <cstdint>

namespace tensorforge {

enum TFTokenKind : uint8_t {
#define TF_TOKEN(X) X,
#define TF_KEYWORD(KEYWORD) TF_TOKEN(kw_##KEYWORD)
#include "TokenMacros.h"
  NUM_TOKENS
};

// Gets a possible keyword from an already valid identifier.
static TFTokenKind getPossibleKWFromID(llvm::StringRef keyword) {
  return llvm::StringSwitch<TFTokenKind>(keyword)
#define TF_KEYWORD(X) .Case(#X, kw_##X)
#include "TensorForge/Frontend/TokenMacros.h"
      .Default(id);
}

static const char *TokenNames[NUM_TOKENS] = {
#define TF_TOKEN(X) #X,
#define TF_KEYWORD(KEYWORD) TF_TOKEN(kw_##KEYWORD)
#include "TensorForge/Frontend/TokenMacros.h"
};

inline static const char *getTokenName(TFTokenKind kind) {
  return TokenNames[kind];
}

struct TFToken {
  const char *Start;
  const char *End;
  TFTokenKind Kind;

  llvm::StringRef getTokenString() const {
    return llvm::StringRef(Start, (End - Start) + 1);
  }
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_TOKEN_H */
