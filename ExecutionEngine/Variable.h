//
// Created by Harris on 15/04/2024.
//

#ifndef PSUDO_INTERPRATOR_2_VARIABLE_H
#define PSUDO_INTERPRATOR_2_VARIABLE_H

union VariableData {
    int integer;
    float real;
    int boolean;
};

struct VariableValue {
    enum TokenType type;
    union VariableData data;
};

struct Variable {
    char* variableName;
    struct VariableValue* value;
};

#endif //PSUDO_INTERPRATOR_2_VARIABLE_H
