#include "Parser.h"
#include "../common/List.h"

void parseDeclare(ASTNode* node, List tokens, int startIndex){
   node->type = DECLARE;
   node->value.declare = (struct ASTDeclare){.type=((Token*)tokens.items[startIndex+3])->type,
                                             .identifier=((Token*)tokens.items[startIndex+1])->lexeme};
}