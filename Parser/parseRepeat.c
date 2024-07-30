#include "Parser.h"
#include "../common/List.h"

int parseRepeat(struct ASTNode* node, struct List* tokens, int startIndex, int endIndex){
   node->type = REPEAT;
   struct List* repeatList = listInit(ASTNode);
   int parsedLen = parse(tokens, repeatList, P_REPEAT, endIndex+1);
   int EndOfUntil = parsedLen + endIndex + 1;
   int startOfUntil = EndOfUntil;
   while (tokens->array[startOfUntil].tokenValue.type != UNTIL){
      startOfUntil--;
   }
   startOfUntil++;
   node->value.Repeat.condition = parseExpression(tokens, startOfUntil, EndOfUntil);
   node->value.Repeat.content = repeatList;
   return parsedLen;
}
