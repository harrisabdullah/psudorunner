#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"
#include "../errors/errors.h"

int parseIf(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   node->type = IF;
   if (((Token*)tokens.items[endIndex-1])->type != THEN){
      e_ifError(startIndex, tokens, code, "Missing 'THEN' at end of line.");
   }
   if (endIndex - startIndex < 3){
      e_ifError(startIndex, tokens, code, "Invalid if statement.");
   }
   node->value.If.test = parseExpression(tokens, startIndex+1, endIndex-2, code);
   struct List* ifList = malloc(sizeof(List));
   if (ifList == NULL){
      ie_allocationError();
   }
   listInit(ifList);
   int offset = parse(ifList, tokens, P_IF, endIndex+1, code);
   if (offset == -1){
      e_ifError(startIndex, tokens, code, "Missing 'ENDIF'.");
   }
   node->value.If.content = ifList;
   return offset;
}