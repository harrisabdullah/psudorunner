//
// Created by Harris on 13/09/2024.
//

#ifndef PSUDO_INTERPRATOR_2_ERRORS_H
#define PSUDO_INTERPRATOR_2_ERRORS_H
#include "../common/List.h"
#include "../Tokenisation/Token.h"

void e_syntaxError(int tokenIndex, List tokens, char* sourceCode, char* message);

void e_forError(int tokenIndex, List tokens, char* sourceCode, char* message);
void e_ifError(int tokenIndex, List tokens, char* sourceCode, char* message);
void e_elseError(int tokenIndex, List tokens, char* sourceCode, char* message);
void e_declareError(int tokenIndex, List tokens, char* sourceCode, char* message);

#endif // PSUDO_INTERPRATOR_2_ERRORS_H