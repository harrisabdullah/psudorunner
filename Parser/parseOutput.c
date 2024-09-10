#include "Parser.h"
#include "../common/List.h"
#include <stdio.h>

void parseOutput(ASTNode* node, List tokens, int startIndex, int endIndex){
   node->type = OUTPUT;
   node->value.output = (struct ASTOutput){.value = parseExpression(tokens, startIndex+1, endIndex-1)};
}
