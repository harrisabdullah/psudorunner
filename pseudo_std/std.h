//
// Created by Harris on 11/09/2024.
//
#ifndef PSUDO_INTERPRATOR_2_STD_H
#define PSUDO_INTERPRATOR_2_STD_H
#include "../Tokenisation/Token.h"
#include "../ExecutionEngine/Variable.h"
#include "../ExecutionEngine/Resolver.h"
#include "../common/List.h"
#include "../common/Stack.h"
#include "../errors/internalErrors.h"
#include <stdlib.h>

extern int STD_FUNC_COUNT;
extern const char* STD_FUNC_IDENTIFIERS[];

void std_INT(List args, struct Stack* stack, List* ns);

extern void (*STD_FUNCS[])(List, struct Stack*, List*);

#endif // PSUDO_INTERPRATOR_2_STD_H