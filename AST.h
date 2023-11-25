//
// Created by Harris on 19/11/2023.
//

#ifndef PSUDO_INTERPRATOR_2_AST_H
#define PSUDO_INTERPRATOR_2_AST_H

enum ASTType {
    DECLARE,
    DATATYPE
};

union ASTData {
    int Int;
    float Float;
};

struct ASTNode {
    enum ASTType type;
    union ASTData data;
    int branchCount;
    struct ASTNode* branches;
};

#endif //PSUDO_INTERPRATOR_2_AST_H
