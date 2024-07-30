//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_PARSER_H
#define PSUDO_INTERPRATOR_2_PARSER_H
#include "ASTNode.h"

enum ParserStatus {
   P_NORMAL,
   P_IF,
   P_ELSE,
   P_WHILE,
   P_REPEAT
};

void parseDeclare(struct ASTNode* node, struct List* tokens, int startIndex);
void parseAssignment(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex);
void parseOutput(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex);

int parseIf(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex);
int parseElse(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex);
int parseWhile(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex);
int parseRepeat(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex);

struct Expression* parseExpression(struct List* tokens, int startIndex, int endIndex);
int parse(struct List* tokens, struct List* ASTList, enum ParserStatus status, int startIndex);

// debug functions
void printASTList(struct List* AST);
void printExpression(struct Expression* expression);
#endif //PSUDO_INTERPRATOR_2_PARSER_H
