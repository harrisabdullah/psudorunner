//
// Created by Harris on 09/04/2024.
//

#ifndef PSUDO_INTERPRATOR_2_NAMESPACE_H
#define PSUDO_INTERPRATOR_2_NAMESPACE_H
#include "../Tokenisation/token.h"
#include "../common/List.h"
#include "../common/Stack.h"
#include "Variable.h"

struct List* namespaceInit();
void namespaceAppend(struct List* namespaceList, char* identifier, enum TokenType type);
void namespaceAssign(struct List* namespace, struct Identifier identifier, struct Expression* data, struct Stack* stack);

#endif //PSUDO_INTERPRATOR_2_NAMESPACE_H
