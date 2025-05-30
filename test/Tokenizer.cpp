#include <gtest/gtest.h>
#include "tokenizerTestUtils.h"

extern "C" {
  #include "Tokenisation/Tokenizer.h"
}

TEST(Tokenizer, OneChar) {
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

TEST(Tokenizer, Keywords) {
  const char* code =
    "IF ELSE THEN ENDIF <- <> MOD <= >= OR AND NOT "
    "BOOLEAN INTEGER REAL STRING OUTPUT DECLARE WHILE ENDWHILE "
    "REPEAT UNTIL FOR TO NEXT";
  TokenType expected[] = {
    IF, ELSE, THEN, ENDIF,
    ASSIGNMENT, NOT_EQUALS, MODULO, LESSER_OR_EQUALS, GREATER_OR_EQUALS,
    OR, AND, NOT,
    BOOLEAN_IDENTIFIER, INTEGER_IDENTIFIER, REAL_IDENTIFIER, STRING_IDENTIFIER,
    OUTPUT, DECLARE, WHILE, ENDWHILE,
    REPEAT, UNTIL, FOR, TO, NEXT
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expected);
}