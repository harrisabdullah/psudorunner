//
// Created by Harris on 05/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_PARSER_H
#define PSUDO_INTERPRATOR_2_PARSER_H
#include "ASTNode.h"
#include "../common/List.h"

enum ParserStatus {
   P_NORMAL,
   P_IF,
   P_ELSE,
   P_WHILE,
   P_REPEAT,
   P_FOR,
};

void parseDeclare(ASTNode* node, List tokens, int startIndex);
void parseAssignment(ASTNode* node, List tokens, int startIndex, int endIndex);
void parseOutput(ASTNode* node, List tokens, int startIndex, int endIndex);

int parseIf(ASTNode* node, List tokens, int startIndex, int endIndex);
int parseElse(ASTNode* node, List tokens, int startIndex, int endIndex);
int parseWhile(ASTNode* node, List tokens, int startIndex, int endIndex);
int parseRepeat(ASTNode* node, List tokens, int startIndex, int endIndex);
int parseFor(ASTNode* node, List tokens, int startIndex, int endIndex);

struct FuncCall parseFuncCall(List tokens, int startIndex, int endIndex);

int isTypeIdentifier(Token* t);
int findClosingParen(int openParenIndex, List tokens, int endIndex, enum TokenType open, enum TokenType close);

struct Expression* parseExpression(List tokens, int startIndex, int endIndex);
int parse(List* ASTList, List tokens, enum ParserStatus status, int startIndex);

// debug functions
void printASTList(List AST);
void printExpression(struct Expression* expression);
#endif //PSUDO_INTERPRATOR_2_PARSER_H
