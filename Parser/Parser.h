//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_PARSER_H
#define PSUDO_INTERPRATOR_2_PARSER_H

struct Expression* parseExpression(struct List* tokens, int startIndex, int endIndex);
struct List* parse(struct List* tokens);

#endif //PSUDO_INTERPRATOR_2_PARSER_H
