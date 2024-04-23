//
// Created by Harris on 09/04/2024.
//

#ifndef PSUDO_INTERPRATOR_2_EXECUTIONENGINE_H
#define PSUDO_INTERPRATOR_2_EXECUTIONENGINE_H
#include "../common/List.h"

struct List* executeAST(struct List* ASTList, struct List* namespace);

#endif //PSUDO_INTERPRATOR_2_EXECUTIONENGINE_H
