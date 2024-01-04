//
// Created by Harris on 20/11/2023.
//

#ifndef PSUDO_INTERPRATOR_2_TOKENIZER_H
#define PSUDO_INTERPRATOR_2_TOKENIZER_H
#include "../common/List.h"
#include "Token.h"

// helper function
static int isKeyword(const char* keyword, int keywordLen, const char* code, int currantCodeIndex, int codeLen);

// tokenize text units
int tokenizeOneChar(char Char, struct List* tokens);
int tokenizeKeywords(const char* code, int currentCodeIndex, int codeLen, struct List* tokens);
int tokenizeNumber(const char* code, int currentCodeIndex, int codeLen, struct List* tokens);
int tokenizeIdentifier(const char* code, int currentCodeIndex, int codeLen, struct List* tokens);

// main tokenizer functions
struct List* tokenize(char* code, int codeLen);

// debug functions
const char* tokenTypeToString(enum TokenType token);
void printToken(struct Token token);
void printTokenList(struct List* tokens);

#endif //PSUDO_INTERPRATOR_2_TOKENIZER_H
