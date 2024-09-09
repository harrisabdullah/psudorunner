#include "Parser.h"
#include "../common/List.h"
#include "../errors/internalErrors.h"

int parseRepeat(ASTNode* node, List tokens, int startIndex, int endIndex){
   node->type = REPEAT;
   struct List* repeatList = malloc(sizeof(List));
   if (repeatList == NULL){
      ie_allocationError();
   }
   listInit(repeatList);

   int parsedLen = parse(repeatList, tokens, P_REPEAT, endIndex+1);
   int EndOfUntil = parsedLen + endIndex + 1;
   int startOfUntil = EndOfUntil;
   while (((Token*)tokens.items[startOfUntil])->type != UNTIL){
      startOfUntil--;
   }
   startOfUntil++;
   node->value.Repeat.condition = parseExpression(tokens, startOfUntil, EndOfUntil);
   node->value.Repeat.content = repeatList;
   return parsedLen;
}
