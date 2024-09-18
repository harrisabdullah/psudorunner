#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"

int parseWhile(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   node->type = WHILE;
   node->value.While.condition = parseExpression(tokens, startIndex+1, endIndex-2, code);
   struct List* whileList = malloc(sizeof(List));
   if (whileList == NULL){
      ie_allocationError();
   }
   listInit(whileList);
   int offset = parse(whileList, tokens, P_WHILE, endIndex+1, code);
   node->value.While.content = whileList;
   return offset;
}
