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

TEST(Tokenizer, booleanValues) {
  const char* code = "TRUE FALSE";
  TokenType expectedTypes[] = { BOOLEAN, BOOLEAN };
  const char* expectedLexemes[] = { "TRUE", "FALSE" };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

TEST(Tokenizer, numbers) {
  const char* code = "123 45.67\n890";
  TokenType expectedTypes[] = {
    INTEGER, REAL, NEW_LINE, INTEGER
  };
  const char* expectedLexemes[] = {
    "123", "45.67", "", "890"
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

TEST(Tokenizer, Identifiers) {
  const char* code = "foo bar123 var_name\n";
  TokenType expectedTypes[] = {
    IDENTIFIER, IDENTIFIER, IDENTIFIER, NEW_LINE
  };
  const char* expectedLexemes[] = {
    "foo", "bar123", "var_name", ""
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

TEST(Tokenizer, StringLiterals) {
  const char* code = "\"hello\" \"She said \\\"Hi\\\"\"\n";
  TokenType expectedTypes[] = {
    STRING, STRING, NEW_LINE
  };
  const char* expectedLexemes[] = {
    "hello", "She said \\\"Hi\\\"", ""
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

TEST(Tokenizer, KeywordVsIdentifier) {
  const char* code = "IFx STRINGer ENDIfElse";
  TokenType expectedTypes[] = {
    IDENTIFIER, IDENTIFIER, IDENTIFIER
  };
  const char* expectedLexemes[] = {
    "IFx", "STRINGer", "ENDIfElse"
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

// TODO: fix this.
// TEST(Tokenizer, LeadingUnderscoreIdentifier) {
//   const char* code = "_foo bar";
//   TokenType expectedTypes[] = {
//     IDENTIFIER
//   };
//   const char* expectedLexemes[] = {
//     "bar"
//   };

//   List result = tokenize(const_cast<char*>(code), strlen(code));
//   ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
//   ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
// }

TEST(Tokenizer, NumberEdgeCases) {
  const char* code = ".5 123. 1.2.3";
  TokenType expectedTypes[] = {
    REAL, REAL, REAL, REAL
  };
  const char* expectedLexemes[] = {
    ".5", "123.", "1.2", ".3"
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

TEST(Tokenizer, LineNumbers) {
  const char* code = "foo\nbar\nbaz";
  TokenType expectedTypes[] = {
    IDENTIFIER, NEW_LINE,
    IDENTIFIER, NEW_LINE,
    IDENTIFIER
  };
  const char* expectedLexemes[] = {
    "foo", "", "bar", "", "baz"
  };
  int expectedLines[] = {
    0, 0,
    1, 1,
    2
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
  ASSERT_TOKEN_LINES_EQ(result, expectedLines);
}

TEST(Tokenizer, WhitespaceAndUnrecognized) {
  const char* code = " \t@#foo   $%^bar";
  TokenType expectedTypes[] = {
    IDENTIFIER, IDENTIFIER
  };
  const char* expectedLexemes[] = {
    "foo", "bar"
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}

TEST(Tokenizer, AdjacentTokensNoSpaces) {
  const char* code = "foo123+\"bar\"";
  TokenType expectedTypes[] = {
    IDENTIFIER, ADDITION, STRING
  };
  const char* expectedLexemes[] = {
    "foo123", "", "bar"
  };

  List result = tokenize(const_cast<char*>(code), strlen(code));
  ASSERT_TOKEN_LIST_EQ(result, expectedTypes);
  ASSERT_TOKEN_LEXEMES_EQ(result, expectedLexemes);
}
