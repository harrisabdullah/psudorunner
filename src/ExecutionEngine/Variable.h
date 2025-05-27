//
// Created by Harris on 15/04/2024.
//

#ifndef PSUDO_INTERPRATOR_2_VARIABLE_H
#define PSUDO_INTERPRATOR_2_VARIABLE_H
#include <stdlib.h>
#include "../Tokenisation/Token.h"

union VariableData {
    int integer;
    float real;
    int boolean;
    char* string;
    char character;
};

struct VariableValue {
    enum TokenType type;
    union VariableData data;
};

typedef struct Variable {
    char* variableName;
    struct VariableValue* value;
} Variable;

inline void freeVariable(struct Variable* pointer){
    free(pointer->variableName);
    free(pointer->value);
    free(pointer);
}

#endif //PSUDO_INTERPRATOR_2_VARIABLE_H
