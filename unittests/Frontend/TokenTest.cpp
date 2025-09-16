// TokenTest.cpp
#include "TensorForge/Frontend/Token.h"
#include <gtest/gtest.h>
#include <iostream>
#include <utility>

using namespace llvm;
using namespace tensorforge;

class TFTokenKindStrPairTests
    : public testing::TestWithParam<std::pair<StringRef, TFTokenKind>> {};

INSTANTIATE_TEST_SUITE_P(
    ValidKeywords, TFTokenKindStrPairTests,
    ::testing::Values(
        std::make_pair("def", kw_def), std::make_pair("return", kw_return),
        std::make_pair("if", kw_if), std::make_pair("else", kw_else),
        std::make_pair("for", kw_for), std::make_pair("in", kw_in),
        std::make_pair("and", kw_and), std::make_pair("or", kw_or),
        std::make_pair("not", kw_not), std::make_pair("tensor", kw_tensor),
        std::make_pair("float64", kw_float64),
        std::make_pair("float32", kw_float32),
        std::make_pair("float16", kw_float16),
        std::make_pair("int32", kw_int32), std::make_pair("int8", kw_int64)));

TEST_P(TFTokenKindStrPairTests, testGetKeywordKind) {
  auto [keyword, expected] = GetParam();
  EXPECT_EQ(getPossibleKWFromID(keyword), expected);
}

TEST(TFTokenKindStrPairTests, testGetKeywordKindInvalid) {
  EXPECT_EQ(getPossibleKWFromID("invalid_keyword"), id);
  EXPECT_EQ(getPossibleKWFromID("identifier"), id);
  EXPECT_EQ(getPossibleKWFromID("IF"), id); // Case sensitive
}

TEST_P(TFTokenKindStrPairTests, testGetTokenName) {
  auto [keyword, kind] = GetParam();
  std::cout << getTokenName(kind) << '\n';
  EXPECT_EQ(getTokenName(kind), keyword);
}
