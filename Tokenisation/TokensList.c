//
// Created by Harris on 04/12/2023.
//
#define ARRAY_SIZE 50

#include "TokensList.h"
#include <stdlib.h>

struct TokenList* tokenListInit() {
    struct TokenList *tokens = malloc(sizeof(struct TokenList));

    if (tokens == NULL){
        perror("Allocation Error: unable to allocate structure TokenList");
        exit(EXIT_FAILURE);
    }

    tokens->tokenArray = malloc(sizeof(struct Token) * ARRAY_SIZE);
    tokens->length = ARRAY_SIZE;

    if (tokens->tokenArray == NULL){
        perror("Allocation Error: unable to allocate TokenList->tokenArray");
        exit(EXIT_FAILURE);
    }

    return tokens;
};

struct TokenList* tokenListAppend(struct TokenList* tokenList, struct Token token){
    if (tokenList->currantIndex >= tokenList->length){
        tokenList->length += 50;
        tokenList->tokenArray = realloc(tokenList->tokenArray, tokenList->length * sizeof(struct Token));

        if (tokenList->tokenArray == NULL){
            perror("Allocation Error: failed to re-allocate TokenList->tokenArray");
            exit(EXIT_FAILURE);
        }
    }

    tokenList->tokenArray[tokenList->currantIndex] = token;
    tokenList->currantIndex++;
};

struct Token* getPrevious(struct TokenList* tokenList){
    if (tokenList->currantIndex == 0){
        return NULL;
    }
    return &tokenList->tokenArray[tokenList->currantIndex-1];
};