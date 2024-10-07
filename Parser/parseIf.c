#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"
#include "../errors/parserErrors.h"

int parseIf(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   node->type = IF;
   if (((Token*)tokens.items[endIndex-1])->type != THEN){
      pe_ifError(((Token*)tokens.items[startIndex])->lineNum, code, "Missing 'THEN' at end of line.");
   }
   if (endIndex - startIndex < 3){
      pe_ifError(((Token*)tokens.items[startIndex])->lineNum, code, "Invalid if statement.");
   }
   node->value.If.test = parseExpression(tokens, startIndex+1, endIndex-2, code);
   struct List* ifList = malloc(sizeof(List));
   if (ifList == NULL){
      ie_allocationError();
   }
   listInit(ifList);
   int offset = parse(ifList, tokens, P_IF, endIndex+1, code);
   if (offset == -1){
      pe_ifError(((Token*)tokens.items[startIndex])->lineNum, code, "Missing 'ENDIF'.");
   }
   node->value.If.content = ifList;
   return offset;
}