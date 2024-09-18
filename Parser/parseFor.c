#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"
#include "../errors/errors.h"

int parseFor(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   node->type = FOR;
   if (((Token*)tokens.items[startIndex+1])->type != IDENTIFIER){
      e_forError(startIndex, tokens, code, "Invalid for loop identifier.");
   }
   if (((Token*)tokens.items[startIndex+2])->type != ASSIGNMENT){
      e_forError(startIndex, tokens, code, "For loop has no '<-'.");
   }
   node->value.For.identifier = (struct Identifier){.lexeme = ((Token*)tokens.items[startIndex+1])->lexeme,
                                                   .hasIndex = 0};

   int toIndex = startIndex;
   while (((Token*)tokens.items[toIndex])->type != TO){
      toIndex++;
      if (toIndex > endIndex){
         e_forError(startIndex, tokens, code, "For loop has no 'TO'.");
      }
   }
   if (startIndex+3 > toIndex-1 || toIndex+1 > endIndex-1){
      e_forError(startIndex, tokens, code, "Invalid for loop range.");
   }
   node->value.For.rangeMin = parseExpression(tokens, startIndex+3, toIndex-1, code);
   node->value.For.rangeMax = parseExpression(tokens, toIndex+1, endIndex-1, code);
   
   struct List* forList = malloc(sizeof(List));
   if (forList == NULL){
      ie_allocationError();
   }
   listInit(forList);
   int offset = parse(forList, tokens, P_FOR, endIndex+1, code);
   node->value.For.content = forList;

   return offset;
}