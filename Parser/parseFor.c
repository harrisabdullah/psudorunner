#include "parser.h"
#include "../common/List.h"

int parseFor(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = FOR;
   node->value.For.identifier = (struct Identifier){.lexeme = tokens->array[startIndex+1].tokenValue.lexeme,
                                                   .hasIndex = 0};

   int toIndex = startIndex+1;
   while (tokens->array[toIndex].tokenValue.type != TO){
      toIndex++;
   }
   node->value.For.rangeMin = parseExpression(tokens, startIndex+3, toIndex-1);
   node->value.For.rangeMax = parseExpression(tokens, toIndex+1, endIndex-1);
   
   struct List* forList = listInit(ASTNode);
   int offset = parse(tokens, forList, P_FOR, endIndex+1);
   node->value.For.content = forList;

   return offset;
}