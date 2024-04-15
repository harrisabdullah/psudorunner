//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_ASTNODE_H
#define PSUDO_INTERPRATOR_2_ASTNODE_H
#include "../common/List.h"
#include "../Tokenisation/Token.h"
#include "Expression.h"

struct ASTDeclare {
    char* identifier;
    enum TokenType type;
};

struct ASTOutput {
    struct Expression* value;
};

struct ASTAssignment {
    char* identifier;
    struct Expression* value;
};

union ASTNodeValue {
    struct ASTDeclare declare;
    struct ASTAssignment assignment;
    struct ASTOutput output;
};

struct ASTNode {
    enum TokenType type;
    union ASTNodeValue value;
};

#endif //PSUDO_INTERPRATOR_2_ASTNODE_H
