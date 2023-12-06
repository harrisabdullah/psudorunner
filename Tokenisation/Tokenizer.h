//
// Created by Harris on 20/11/2023.
//

#ifndef PSUDO_INTERPRATOR_2_TOKENIZER_H
#define PSUDO_INTERPRATOR_2_TOKENIZER_H
#include "TokensList.h"

enum TokenType {
    NULL_TOKEN,
    DECLARE, // DECLARE statement e.g. "DECLARE i: INTEGER"
    IDENTIFIER, // names of function or variables e.g. `i`
    INTEGER_IDENTIFIER, // the integer type e.g. the "INTEGER" in "DECLARE i: INTEGER"
    REAL_IDENTIFIER, // the real type
    INTEGER, // integer values e.g. "1", "23", "-444"
    REAL, // real values e.g. "1.1", "-23.0", "22.22"
    ASSIGNMENT, // the assignment operator e.g. the "<-" in "i <- 5"
    ADDITION, // the addition operator e.g. "1+1"
    SUBTRACTION, // the subtraction operator e.g. "2-1"
    DIVISION, // the division operator e.g. "4/2"
    MULTIPLICATION, // the multiplication operator e.g. "3*3"
    OPEN_PAREN, // open parenthesis
    CLOSE_PAREN, // close parenthesis
    NEW_LINE, // used to terminate statements e.g. the semicolon in c
};

struct Token {
    enum TokenType type;
    char* lexeme; // TODO: consider using linked list or something similar
    int lexemeLen;
};

struct TokenArray{
    struct Token* tokens;
    int len;
};

// tokenize text units
void tokenizeOneChar(char Char, struct, struct TokenList* tokens);
static int isKeyword(const char* keyword, int keywordLen, const char* code, int currantCodeIndex, int codeLen);
void tokenizeKeywords(const char* code, int currantCodeIndex, int codeLen, struct TokenList* currantToken);
static int tokenizeNumber(const char* code, int currantCodeIndex, int codeLen, struct Token* currantToken);

// main tokenizer functions
static int tokenize(const char* code, int codeLen, int currantCodeIndex, struct Token* currantToken, struct Token* )
struct TokenArray tokenize(char* code, int codeLen);

// debug functions
const char* tokenTypeToString(enum TokenType token);
void printTokenArray(struct TokenArray tokens);


#endif //PSUDO_INTERPRATOR_2_TOKENIZER_H
