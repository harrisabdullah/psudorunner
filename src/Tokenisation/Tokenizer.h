//
// Created by Harris on 20/11/2023.
//

#ifndef PSUDO_INTERPRATOR_2_TOKENIZER_H
#define PSUDO_INTERPRATOR_2_TOKENIZER_H
#include "../common/List.h"
#include "Token.h"

#ifdef __cplusplus
extern "C"
{
#endif

// tokenize text units
int tokenizeOneChar(Token* token, Token* previouseToken, char Char);
int tokenizeKeywords(Token* token, const char* code, int currentCodeIndex, int codeLen);
int tokenizeNumber(Token* token, const char* code, int currentCodeIndex, int codeLen);
int tokenizeIdentifier(Token* token, const char* code, int currentCodeIndex, int codeLen);
int tokenizeString(Token* token, const char* code, int currentCodeIndex, int codeLen);

// main tokenizer functions
struct List tokenize(char* code, int codeLen);

// debug functions
void printToken(struct Token* token);
void printTokenList(List tokens);

#ifdef __cplusplus
}
#endif
#endif //PSUDO_INTERPRATOR_2_TOKENIZER_H
