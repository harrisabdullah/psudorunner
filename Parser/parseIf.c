#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"

int parseIf(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   node->type = IF;
   node->value.If.test = parseExpression(tokens, startIndex+1, endIndex-2, code);
   struct List* ifList = malloc(sizeof(List));
   if (ifList == NULL){
      ie_allocationError();
   }
   listInit(ifList);
   int offset = parse(ifList, tokens, P_IF, endIndex+1, code);
   node->value.If.content = ifList;
   return offset;
}