#include "Parser.h"
#include "../Common/List.h"

void parseDeclare(struct ASTNode* node, struct List* tokens, int startIndex){
   node->type = DECLARE;
   node->value.declare = (struct ASTDeclare){.type=tokens->array[startIndex+3].tokenValue.type,
                                             .identifier=tokens->array[startIndex+1].tokenValue.lexeme};
}