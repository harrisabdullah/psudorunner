#include "syntaxChecker.h"
#include "errors.h"
#include <stdio.h>

void syn_checkConst(int tokenIndex, List tokens, char* sourceCode){
   if (((Token*)(tokens.items[tokenIndex]))->type != INTEGER &&
       ((Token*)(tokens.items[tokenIndex]))->type != STRING && 
       ((Token*)(tokens.items[tokenIndex]))->type != REAL && 
       ((Token*)(tokens.items[tokenIndex]))->type != BOOLEAN) {
         e_syntaxError(tokenIndex, tokens, sourceCode, "Invalid Expression.");
       }
}