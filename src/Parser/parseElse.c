#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"
#include "../errors/parserErrors.h"

#include <stdio.h>

int parseElse(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   if (endIndex - startIndex > 1){
      pe_elseError(((Token*)tokens.items[startIndex])->lineNum, code, "Invalid else statement.");
   }
   node->type = ELSE;
   List* elseList = malloc(sizeof(List));
   if (elseList == NULL){
      ie_allocationError();
   }
   listInit(elseList);
   int offset = parse(elseList, tokens, P_ELSE, endIndex+1, code);
   if (offset == -1){
      pe_elseError(((Token*)tokens.items[startIndex])->lineNum, code, "Missing 'ENDIF'.");
   }
   node->value.Else.content = elseList;
   return offset;
}