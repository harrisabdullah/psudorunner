#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"

int parseElse(ASTNode* node, List tokens, int startIndex, int endIndex){
   node->type = ELSE;
   List* elseList = malloc(sizeof(List));
   if (elseList == NULL){
      ie_allocationError();
   }
   listInit(elseList);
   int offset = parse(elseList, tokens, P_ELSE, endIndex+1);
   node->value.Else.content = elseList;
   return offset;
}