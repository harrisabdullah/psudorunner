#include "Parser.h"
#include "../Common/List.h"

int parseWhile(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = WHILE;
   node->value.While.condition = parseExpression(tokens, startIndex+1, endIndex-2);
   struct List* whileList = listInit(ASTNode);
   int offset = parse(tokens, whileList, P_IF, endIndex+1);
   node->value.While.content = whileList;
   return offset;
}
