#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"

int parseFor(ASTNode* node, List tokens, int startIndex, int endIndex){
   node->type = FOR;
   node->value.For.identifier = (struct Identifier){.lexeme = ((Token*)tokens.items[startIndex+1])->lexeme,
                                                   .hasIndex = 0};

   int toIndex = startIndex+1;
   while (((Token*)tokens.items[toIndex])->type != TO){
      toIndex++;
   }
   node->value.For.rangeMin = parseExpression(tokens, startIndex+3, toIndex-1);
   node->value.For.rangeMax = parseExpression(tokens, toIndex+1, endIndex-1);
   
   struct List* forList = malloc(sizeof(List));
   if (forList == NULL){
      ie_allocationError();
   }
   listInit(forList);
   int offset = parse(forList, tokens, P_FOR, endIndex+1);
   node->value.For.content = forList;

   return offset;
}