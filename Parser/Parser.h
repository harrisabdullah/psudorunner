//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_PARSER_H
#define PSUDO_INTERPRATOR_2_PARSER_H

struct Expression* parseExpression(struct List* tokens, int startIndex, int endIndex);
struct List* parse(struct List* tokens, int start_index, int end_index);

// debug functions
void printASTList(struct List* AST);
void printExpression(struct Expression* expression);
#endif //PSUDO_INTERPRATOR_2_PARSER_H
