// tests/TokenTestUtils.h
#ifndef TOKEN_TEST_UTILS_H
#define TOKEN_TEST_UTILS_H

#include <gtest/gtest.h>
#include <vector>
#include <ostream>
#include <cstring>
extern "C" {
  #include "Tokenisation/Tokenizer.h"
}

// 1) Pretty-printer for TokenType
inline const char* TokenTypeToString(TokenType t) {
  switch (t) {
    case ADDITION:           return "ADDITION";
    case SUBTRACTION:        return "SUBTRACTION";
    case DIVISION:           return "DIVISION";
    case MULTIPLICATION:     return "MULTIPLICATION";
    case OPEN_PAREN:         return "OPEN_PAREN";
    case CLOSE_PAREN:        return "CLOSE_PAREN";
    case COLON:              return "COLON";
    case EQUALS:             return "EQUALS";
    case LESSER:             return "LESSER";
    case COMMA:              return "COMMA";
    case GREATER:            return "GREATER";
    case OPEN_SQUARE_PAREN:  return "OPEN_SQUARE_PAREN";
    case CLOSE_SQUARE_PAREN: return "CLOSE_SQUARE_PAREN";
    case NEW_LINE:           return "NEW_LINE";
    default:                 return "UNKNOWN_TOKEN";
  }
}

inline std::ostream& operator<<(std::ostream& os, TokenType t) {
  return os << TokenTypeToString(t);
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

TEST(Tokenizer, oneChar) {
  const char* code = "+-/*():=<,>[]\n";
  TokenType expected[] = {
    ADDITION, SUBTRACTION, DIVISION, MULTIPLICATION,
    OPEN_PAREN, CLOSE_PAREN, COLON, EQUALS, LESSER,
    COMMA, GREATER, OPEN_SQUARE_PAREN, CLOSE_SQUARE_PAREN,
    NEW_LINE
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expected);
}
