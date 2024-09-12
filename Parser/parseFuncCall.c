#include "../common/List.h"
#include "../common/tokenTypeToString.h"
#include "Expression.h"
#include "Parser.h"
#include <stdio.h>

struct FuncCall parseFuncCall(List tokens, int startIndex, int endIndex){
   struct FuncCall funcCall;

   if (isTypeIdentifier((Token*)tokens.items[startIndex])){
      funcCall.lexeme = (char*)tokenTypeToString(((Token*)tokens.items[startIndex])->type);
   } else {
      funcCall.lexeme = ((Token*)tokens.items[startIndex])->lexeme;
   }
   listInit(&funcCall.args);
   if (endIndex - startIndex == 2){
      return funcCall;
   }

   int argStart = startIndex + 1;
   int argEnd = argStart;
   while (argEnd != endIndex){
      argStart = argEnd + 1;
      argEnd = argStart;
      while (((Token*)tokens.items[argEnd])->type != COMMA && 
             ((Token*)tokens.items[argEnd])->type != CLOSE_PAREN){
         argEnd++;
      }
      listAppend(&funcCall.args, parseExpression(tokens, argStart, argEnd-1));
   }
   return funcCall;
}
