//
// Created by Harris on 09/04/2024.
//

#ifndef PSUDO_INTERPRATOR_2_RESOLVER_H
#define PSUDO_INTERPRATOR_2_RESOLVER_H
#include "../Parser/Expression.h"
#include "../common/Stack.h"
#include "Namespace.h"
#include "Variable.h"

struct VariableValue* stringToVariableValue(enum TokenType type, char* data, struct List* namespace);
void resolveExpression(struct List* namespace, struct Expression* expression, struct Stack* stack);
#endif //PSUDO_INTERPRATOR_2_RESOLVER_H
