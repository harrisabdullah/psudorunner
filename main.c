#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"
#include <stdio.h>
#include <string.h>

int main() {
   char* code = "DECLARE i: INTEGER\nFOR i <- 1 TO 5\nOUTPUT i \n NEXT i";
   List tokens = tokenize(code, strlen(code));
   printTokenList(tokens);
    List* AST = malloc(sizeof(List));
   listInit(AST);
   parse(AST, tokens, P_NORMAL, 0, code);
   printASTList(*AST);
   List* namespace = malloc(sizeof(List));
   listInit(namespace);
   printf("----------------------------\n");
   executeAST(*AST, namespace);
}
