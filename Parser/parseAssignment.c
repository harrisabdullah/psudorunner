#include "Parser.h"

void parseAssignment(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   struct Identifier identifer;
   identifer.hasIndex = 0;
   node->type = ASSIGNMENT;
   int arrowIndex = startIndex+1;
      printf("here\n");

   if (tokens->array[startIndex+1].tokenValue.type == OPEN_SQUARE_PAREN){
      int i = startIndex+2;
      while (tokens->array[i].tokenValue.type != CLOSE_SQUARE_PAREN){
         i++;
      }
      identifer.hasIndex = 1;
      identifer.indexExpression = parseExpression(tokens, startIndex+2, i-1);
      arrowIndex = i+1;
   }
   identifer.lexeme = tokens->array[startIndex].tokenValue.lexeme;
   node->value.assignment = (struct ASTAssignment){.identifier = identifer,
                                                   .value = parseExpression(tokens, arrowIndex+1, endIndex-1)};
                     
}
