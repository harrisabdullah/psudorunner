#include <gtest/gtest.h>
#include "tokenizerTestUtils.h"

extern "C" {
  #include "Tokenisation/Tokenizer.h"
}

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
