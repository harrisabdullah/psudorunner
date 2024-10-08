//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_ASTNODE_H
#define PSUDO_INTERPRATOR_2_ASTNODE_H
#include "../Tokenisation/Token.h"
#include "Expression.h"

struct ASTDeclare {
    char* identifier;
    enum TokenType type;
};

struct ASTOutput {
    struct Expression* value;
};

struct ASTif {
    struct Expression* test;
    struct List* content;
};

struct ASTElse {
    struct List* content;
};

struct ASTWhile { 
    struct Expression* condition;
    struct List* content;
};

struct ASTRepeat {
    struct List* content;
    struct Expression* condition;
};

struct ASTFor {
    struct Identifier identifier;
    struct Expression* rangeMin;
    struct Expression* rangeMax;
    struct List* content;
};

struct ASTAssignment {
    struct Identifier identifier;
    struct Expression* value;
};

union ASTNodeValue {
    struct ASTDeclare declare;
    struct ASTAssignment assignment;
    struct ASTOutput output;
    struct ASTif If;
    struct ASTElse Else;
    struct ASTWhile While;
    struct ASTRepeat Repeat;
    struct ASTFor For;
};

typedef struct ASTNode {
    enum TokenType type;
    union ASTNodeValue value;
} ASTNode;

#endif //PSUDO_INTERPRATOR_2_ASTNODE_H
