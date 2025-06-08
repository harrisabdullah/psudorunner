#ifndef TOKEN_TEST_UTILS_H
#define TOKEN_TEST_UTILS_H

#include <gtest/gtest.h>
#include <vector>
#include <ostream>
#include <cstring>
#include <string>
extern "C" {
  #include "Tokenisation/Tokenizer.h"
  #include "common/tokenTypeToString.h"
}

// Pretty-print TokenType in failure messages
inline std::ostream& operator<<(std::ostream& os, TokenType t) {
  return os << tokenTypeToString(t);
}

// Core comparison by type
inline ::testing::AssertionResult CompareTokenLists(
    const char* exprList,
    const char* exprExp,
    const List& actualList,
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

#define ASSERT_TOKEN_LIST_EQ(list, expected_array)                          \
  do {                                                                      \
    std::vector<TokenType> _exp(                                            \
      std::begin(expected_array), std::end(expected_array));                \
    ASSERT_PRED_FORMAT2(CompareTokenLists, list, _exp);                     \
  } while (0)

// Compare lexemes
inline ::testing::AssertionResult CompareTokenLexemes(
    const char* exprList,
    const char* exprExp,
    const List& actualList,
    const std::vector<std::string>& expected)
{
  if (actualList.length != expected.size()) {
    return ::testing::AssertionFailure()
      << "Length mismatch: " << exprList << ".length ("
      << actualList.length << ") != " << exprExp << ".size() ("
      << expected.size() << ")";
  }
  for (size_t i = 0; i < expected.size(); ++i) {
    const char* rawLex = static_cast<Token*>(actualList.items[i])->lexeme;
    std::string gotLex = rawLex ? rawLex : "";
    if (gotLex != expected[i]) {
      return ::testing::AssertionFailure()
        << "Lexeme mismatch at index " << i
        << ": got \"" << gotLex << "\""
        << ", expected \"" << expected[i] << "\"";
    }
  }
  return ::testing::AssertionSuccess();
}

#define ASSERT_TOKEN_LEXEMES_EQ(list, expected_array)                        \
  do {                                                                      \
    std::vector<std::string> _expStrs(                                      \
      std::begin(expected_array), std::end(expected_array));                \
    ASSERT_PRED_FORMAT2(CompareTokenLexemes, list, _expStrs);               \
  } while (0)

// Compare line numbers
inline ::testing::AssertionResult CompareTokenLines(
    const char* exprList,
    const char* exprExp,
    const List& actualList,
    const std::vector<int>& expected)
{
  if (actualList.length != expected.size()) {
    return ::testing::AssertionFailure()
      << "Length mismatch: " << exprList << ".length ("
      << actualList.length << ") != " << exprExp << ".size() ("
      << expected.size() << ")";
  }
  for (size_t i = 0; i < expected.size(); ++i) {
    int gotLine = static_cast<Token*>(actualList.items[i])->lineNum;
    if (gotLine != expected[i]) {
      return ::testing::AssertionFailure()
        << "Line number mismatch at index " << i
        << ": got " << gotLine
        << ", expected " << expected[i];
    }
  }
  return ::testing::AssertionSuccess();
}

#define ASSERT_TOKEN_LINES_EQ(list, expected_array)                         \
  do {                                                                      \
    std::vector<int> _expLines(                                            \
      std::begin(expected_array), std::end(expected_array));                \
    ASSERT_PRED_FORMAT2(CompareTokenLines, list, _expLines);                \
  } while (0)

#endif // TOKEN_TEST_UTILS_H
