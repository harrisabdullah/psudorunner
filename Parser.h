//
// Created by Harris on 19/11/2023.
//

#ifndef PSUDO_INTERPRATOR_2_PARSER_H
#define PSUDO_INTERPRATOR_2_PARSER_H

#include "AST.h"
#include <stdio.h>

struct ASTNode* parseFile(const char* filename);
struct ASTNode* parseLine(const char* line, ssize_t length, struct ASTNode* previous);

#endif //PSUDO_INTERPRATOR_2_PARSER_H
