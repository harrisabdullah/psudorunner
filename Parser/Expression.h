//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_EXPRESSION_H
#define PSUDO_INTERPRATOR_2_EXPRESSION_H
#include "../Tokenisation/Token.h"

struct Identifier {
    char* lexeme;
    int hasIndex;
    struct Expression* indexExpression;
};

struct Expression {
    enum TokenType type;
    int isConstant;
    struct Expression* left;
    struct Expression* right;
    char* lexeme;
    struct Identifier identifier;
};

#endif //PSUDO_INTERPRATOR_2_EXPRESSION_H
