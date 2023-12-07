//
// Created by Harris on 04/12/2023.
//
#define ARRAY_SIZE 50

#include "TokensList.h"
#include <stdlib.h>

/**
 * Initializes a new TokenList structure.
 *
 * @return A pointer to the newly allocated TokenList structure.
 */
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

/**
 * Appends a Token to the TokenList, reallocating memory if necessary.
 *
 * @param tokenList A pointer to the TokenList structure.
 * @param token The Token to be appended.
 *
 * @return A pointer to the modified TokenList structure.
 */
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

/**
 * Retrieves the previous Token in the TokenList.
 *
 * @param tokenList A pointer to the TokenList structure.
 *
 * @return A pointer to the previous Token in the TokenList, or NULL if at the beginning.
 */
struct Token* tokenListGetPrevious(struct TokenList* tokenList){
    if (tokenList->currantIndex == 0){
        return NULL;
    }
    return &tokenList->tokenArray[tokenList->currantIndex-1];
};

void printTokenList(struct TokenList* tokenList){
    for (int i=0; i<tokenList->currantIndex; i++){
        printToken(tokenList->tokenArray[i]);
    }
};