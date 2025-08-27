// Token.h
#ifndef TF_FRONTEND_TOKEN_H
#define TF_FRONTEND_TOKEN_H

#include <llvm/ADT/StringSwitch.h>

#include <cstdint>

namespace tensorforge {

enum TFTokenKind : uint8_t {
#define TF_TOKEN(X) X,
#include "TokenMacros.h"
  NUM_TOKENS
};

static TFTokenKind getKeywordKind(llvm::StringRef keyword) {
  return llvm::StringSwitch<TFTokenKind>(keyword)
#define TF_KEYWORD(X) .Case(#X, kw_##X)
#include "TokenMacros.h"
      ;
}

static const char *TokenNames[NUM_TOKENS] = {
#define TF_TOKEN(X) #X,
#include "TokenMacros.h"
};

static inline const char *getTokenName(TFTokenKind kind) {
  return TokenNames[kind];
}

struct TFToken {
  const char *Start;
  const char *End;
  TFTokenKind Kind;
};

} // namespace tensorforge
#endif /* ifndef TF_FRONTEND_TOKEN_H */
