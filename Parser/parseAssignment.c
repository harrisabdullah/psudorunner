#include "Parser.h"
#include "../Common/List.h"

void parseAssignment(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = ASSIGNMENT;
   node->value.assignment = (struct ASTAssignment){.identifier = tokens->array[startIndex].tokenValue.lexeme,
                                                   .value = parseExpression(tokens, startIndex+2, endIndex-1)};
                     
}
