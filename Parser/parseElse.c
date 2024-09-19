#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"
#include "../errors/errors.h"

#include <stdio.h>

int parseElse(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   if (endIndex - startIndex > 1){
      e_elseError(startIndex, tokens, code, "Invalid else statement.");
   }
   node->type = ELSE;
   List* elseList = malloc(sizeof(List));
   if (elseList == NULL){
      ie_allocationError();
   }
   listInit(elseList);
   int offset = parse(elseList, tokens, P_ELSE, endIndex+1, code);
   if (offset == -1){
      e_elseError(startIndex, tokens, code, "Missing 'ENDIF'.");
   }
   node->value.Else.content = elseList;
   return offset;
}