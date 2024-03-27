//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_EXPRESSION_H
#define PSUDO_INTERPRATOR_2_EXPRESSION_H
#include "../Tokenisation/Token.h"

struct Expression {
    enum TokenType type;
    struct Expression* left;
    struct Expression* right;
    char* lexeme;
};

#endif //PSUDO_INTERPRATOR_2_EXPRESSION_H
