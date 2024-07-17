#include "Parser.h"
#include "../Common/List.h"
#include <stdio.h>

void parseOutput(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = OUTPUT;
   node->value.output = (struct ASTOutput){.value = parseExpression(tokens, startIndex+1, endIndex-1)};
}
