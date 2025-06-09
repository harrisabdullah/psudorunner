#include "errors.h"
#include "internalErrors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* getLine(int line, char* sourceCode){
   int currantLine = 0;
   int lineStart = 0;
   while (currantLine < line){
      if (sourceCode[lineStart] == '\n'){
         currantLine++;
      }
      lineStart++;
   }

   int lineEnd = lineStart;
   int codeLen = strlen(sourceCode);
   while (lineEnd < codeLen && sourceCode[lineEnd] != '\n'){
      lineEnd++;
   }
   if (lineEnd < codeLen){
      lineEnd--;
   }
   int lineLen = lineEnd - lineStart + 1;
   char* lineStr = malloc(sizeof(char) * lineLen + 1);
   if (lineStr == NULL){
      ie_allocationError();
   }
   for (int i = 0; i < lineLen; i++) {
      lineStr[i] = sourceCode[lineStart + i];
   }
   lineStr[lineLen] = '\0';
   return lineStr;
}

void pe_raise(int line, char* sourceCode, char* catagory, char* message, char* footer){
   char* lineStr = getLine(line, sourceCode);
   fprintf(stderr, "Error on line %d:\n", line+1);
   fprintf(stderr, "%4d | %s\n", line+1, lineStr);
   fprintf(stderr, "%s: %s%s\n", catagory, message, footer);
   exit(EXIT_FAILURE);
}