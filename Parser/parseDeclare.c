#include "Parser.h"
#include "../common/List.h"
#include "../errors/syntaxChecker.h"
#include "../errors/errors.h"
#include "stdio.h"

void parseDeclare(ASTNode* node, List tokens, int startIndex, char* code){

   if (((Token*)tokens.items[startIndex+1])->type != IDENTIFIER){
      e_declareError(startIndex, tokens, code, "Invalid variable name.");
   }
   if (((Token*)tokens.items[startIndex+2])->type != COLON){
      e_declareError(startIndex, tokens, code, "Missing ':'.");
   }
   if (!syn_isConstIdentifier(((Token*)tokens.items[startIndex+3])->type)){
      e_declareError(startIndex, tokens, code, "Invalid datatype.");
   }
   if (tokens.length > 4){
      if (((Token*)tokens.items[startIndex+4])->type != NEW_LINE){
         e_declareError(startIndex, tokens, code, "Invalid declare.");
      }
   }

   node->type = DECLARE;
   node->value.declare = (struct ASTDeclare){.type=((Token*)tokens.items[startIndex+3])->type,
                                             .identifier=((Token*)tokens.items[startIndex+1])->lexeme};
}