//
// Created by Harris on 04/12/2023.
//

#ifndef PSUDO_INTERPRATOR_2_TOKENSLIST_H
#define PSUDO_INTERPRATOR_2_TOKENSLIST_H
#include "Tokenizer.h"
#include <stdio.h>

struct TokenList {
    size_t length;
    int currantIndex;
    struct Token* tokenArray;
};

struct TokenList* tokenListInit();
struct TokenList* tokenListAppend(struct TokenList* tokenList, struct Token token);
struct Token* tokenListGetPrevious(struct TokenList* tokenList);

// debug function
void printTokenList(struct TokenList* tokenList);

#endif //PSUDO_INTERPRATOR_2_TOKENSLIST_H
