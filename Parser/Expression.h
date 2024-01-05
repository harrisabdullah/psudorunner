//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_EXPRESSION_H
#define PSUDO_INTERPRATOR_2_EXPRESSION_H

enum OperationType {
    OP_ADDITION,
    OP_SUBTRACTION,
    OP_MULTIPLICATION,
    OP_DIVISION,
};

enum DataTypes {
    DT_INTEGER,
    DT_REAL
};

union ExpressionValue {
    enum OperationType operation;
    int integer;
    float real;
};

enum ExpressionDataType {
    EX_OPERATION,
    EX_REAL,
    EX_INTEGER
};

struct Expression {
    enum ExpressionDataType type;
    union ExpressionValue value;
    struct Expression* left;
    struct Expression* right;
};

#endif //PSUDO_INTERPRATOR_2_EXPRESSION_H
