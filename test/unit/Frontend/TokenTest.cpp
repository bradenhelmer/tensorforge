// TokenTest.cpp
#include "TensorForge/Frontend/Token.h"
#include <gtest/gtest.h>
#include <utility>

using namespace llvm;
using namespace tensorforge;

class GetKeywordKindTest
    : public testing::TestWithParam<std::pair<StringRef, TFTokenKind>> {};

TEST_P(GetKeywordKindTest, getKeywordKind) {
  auto [keyword, expected] = GetParam();
  EXPECT_EQ(getKeywordKind(keyword), expected);
}

INSTANTIATE_TEST_SUITE_P(
    ValidKeywords, GetKeywordKindTest,
    ::testing::Values(
        std::make_pair("def", kw_def), std::make_pair("return", kw_return),
        std::make_pair("if", kw_if), std::make_pair("else", kw_else),
        std::make_pair("for", kw_for), std::make_pair("in", kw_in),
        std::make_pair("and", kw_and), std::make_pair("or", kw_or),
        std::make_pair("not", kw_not), std::make_pair("tensor", kw_tensor),
        std::make_pair("float32", kw_float32),
        std::make_pair("float16", kw_float16),
        std::make_pair("int32", kw_int32), std::make_pair("int8", kw_int8)));

TEST(TokenTest, getKeywordKindInvalid) {
  EXPECT_EQ(getKeywordKind("invalid_keyword"), invalid);
  EXPECT_EQ(getKeywordKind("identifier"), invalid);
  EXPECT_EQ(getKeywordKind(""), invalid);
  EXPECT_EQ(getKeywordKind("IF"), invalid); // Case sensitive
}
