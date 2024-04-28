//
// Created by Harris on 28/04/2024.
//

#ifndef PSUDO_INTERPRATOR_2_TESTTOKENIZER_H
#define PSUDO_INTERPRATOR_2_TESTTOKENIZER_H

#include "../Tokenisation/Token.h"
#include "../common/List.h"

void testTokenizer();
int compareTokens(struct List* tokens, struct Token test[], int length);
#endif //PSUDO_INTERPRATOR_2_TESTTOKENIZER_H
