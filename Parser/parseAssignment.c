#include "Parser.h"
#include "../errors/errors.h"

void parseAssignment(ASTNode* node, List tokens, int startIndex, int endIndex, char* code){
   if (((Token*)tokens.items[startIndex])->type != IDENTIFIER){
      e_assignmentError(startIndex, tokens, code, "Invalid variable name.");
   }
   struct Identifier identifer;
   identifer.hasIndex = 0;
   node->type = ASSIGNMENT;
   int arrowIndex = startIndex+1;

   if (((Token*)tokens.items[startIndex])->type == OPEN_SQUARE_PAREN){
      int i = startIndex+2;
      while (((Token*)tokens.items[i])->type != CLOSE_SQUARE_PAREN){
         i++;
      }
      identifer.hasIndex = 1;
      identifer.indexExpression = parseExpression(tokens, startIndex+2, i-1, code);
      arrowIndex = i+1;
   }
   identifer.lexeme = ((Token*)tokens.items[startIndex])->lexeme;
   node->value.assignment = (struct ASTAssignment){.identifier = identifer,
                                                   .value = parseExpression(tokens, arrowIndex+1, endIndex-1, code)};
                     
}
