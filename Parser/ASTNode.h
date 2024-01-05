//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_ASTNODE_H
#define PSUDO_INTERPRATOR_2_ASTNODE_H
#include "../common/List.h"
#include "Expression.h"

struct ASTDeclare {
    enum DataTypes type;
    struct Expression* expression;
};

union ASTNodeValue {
    struct ASTDeclare declare;
};

enum ASTNodeTypes {
    AST_DECLARE,
};

struct ASTNode {
    enum ASTNodeTypes type;
    union ASTNodeValue value;
};

#endif //PSUDO_INTERPRATOR_2_ASTNODE_H
