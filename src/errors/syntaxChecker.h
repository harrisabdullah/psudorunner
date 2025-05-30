//
// Created by Harris on 12/09/2024.
//

#ifndef PSUDO_INTERPRATOR_2_SYNTAX_CHECKER_H
#define PSUDO_INTERPRATOR_2_SYNTAX_CHECKER_H
#include "../common/List.h"
#include "../Tokenisation/Token.h"

void syn_checkConst(int line, int tokenIndex, List tokens, char* sourceCode);
int syn_isConstIdentifier(enum TokenType t);

#endif // PSUDO_INTERPRATOR_2_SYNTAX_CHECKER_H