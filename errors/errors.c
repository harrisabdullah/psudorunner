#include "errors.h"
#include "internalErrors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getLineIndex(int tokenIndex, List tokens){
   int line = 0;
   for (int i=0; i<tokenIndex; i++){
      if (((Token*)(tokens.items[i]))->type == NEW_LINE){
         line++;
      }
   }
   return line;
}

char* getLine(int lineIndex, char* sourceCode){
   int currantLine = 0;
   int lineStart = 0;
   while (currantLine < lineIndex){
      if (sourceCode[lineStart] == '\n'){
         currantLine++;
      }
      lineStart++;
   }

   int lineEnd = lineStart;
   int codeLen = strlen(sourceCode); // preformance doesnt matter for error reporting
   while (lineEnd < codeLen && sourceCode[lineEnd] != '\n'){
      lineEnd++;
   }
   if (lineEnd < codeLen){
      lineEnd--;
   }
   int lineLen = lineEnd - lineStart + 1;
   char* line = malloc(sizeof(char) * lineLen + 1);
   if (line == NULL){
      ie_allocationError();
   }
   for (int i = 0; i < lineLen; i++) {
      line[i] = sourceCode[lineStart + i];
   }
   line[lineLen] = '\0';
   return line;
}

void e_raise(int tokenIndex, List tokens, char* sourceCode, char* catagory, char* message){
   int lineIndex = getLineIndex(tokenIndex, tokens);
   char* lineStr = getLine(lineIndex, sourceCode);
   fprintf(stderr, "Error on line %d:\n", lineIndex+1);
   fprintf(stderr, "%4d | %s\n", lineIndex+1, lineStr);
      fprintf(stderr, "%s: %s\n", catagory, message);
   exit(EXIT_FAILURE);
}

void e_syntaxError(int tokenIndex, List tokens, char* sourceCode, char* message){
   e_raise(tokenIndex, tokens, sourceCode, "SyntaxError", message);
}