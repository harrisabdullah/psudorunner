#include "Parser.h"
#include "../Common/List.h"

int parseElse(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = ELSE;
   struct List* elseList = listInit(ASTNode);
   int offset = parse(tokens, elseList, P_ELSE, endIndex+1);
   node->value.Else.content = elseList;
   return offset;
}