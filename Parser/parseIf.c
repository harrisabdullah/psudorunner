#include "parser.h"
#include "../Common/List.h"

int parseIf(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = IF;
   node->value.If.test = parseExpression(tokens, startIndex+1, endIndex);
   struct List* ifList = listInit(ASTNode);
   int offset = parse(tokens, ifList, P_IF, endIndex+1);
   node->value.If.content = ifList;
   return offset;
}