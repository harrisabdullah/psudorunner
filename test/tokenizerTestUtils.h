// tests/TokenTestUtils.h
#ifndef TOKEN_TEST_UTILS_H
#define TOKEN_TEST_UTILS_H

#include <gtest/gtest.h>
#include <vector>
#include <ostream>
#include <cstring>
extern "C" {
  #include "Tokenisation/Tokenizer.h"
  #include "common/tokenTypeToString.h"
}

inline std::ostream& operator<<(std::ostream& os, TokenType t) {
  return os << tokenTypeToString(t);
}

// 2) Core comparison function returning an AssertionResult
inline ::testing::AssertionResult CompareTokenLists(
    const char* exprList,
    const char* exprExp,
    const List&   actualList,
    const std::vector<TokenType>& expected)
{
  if (actualList.length != expected.size()) {
    return ::testing::AssertionFailure()
      << "Length mismatch: " << exprList << ".length ("
      << actualList.length << ") != " << exprExp << ".size() ("
      << expected.size() << ")";
  }

  for (size_t i = 0; i < expected.size(); ++i) {
    TokenType got = static_cast<Token*>(actualList.items[i])->type;
    if (got != expected[i]) {
      return ::testing::AssertionFailure()
        << "Mismatch at index " << i
        << ": got " << got
        << ", expected " << expected[i];
    }
  }

  return ::testing::AssertionSuccess();
}

// 3) Convenient macro for one-liner in tests
#define ASSERT_TOKEN_LIST_EQ(list, expected_array)                          \
  do {                                                                      \
    std::vector<TokenType> _exp(                                            \
      std::begin(expected_array), std::end(expected_array));                \
    ASSERT_PRED_FORMAT2(CompareTokenLists, list, _exp);                     \
  } while (0)

#endif // TOKEN_TEST_UTILS_H
