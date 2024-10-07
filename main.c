#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"
#include <stdio.h>
#include <string.h>

int main() {
   char* code = "DECLAR";
   List tokens = tokenize(code, strlen(code));
   printTokenList(tokens);
   printf("\n");
   List* AST = malloc(sizeof(List));
   listInit(AST);
   parse(AST, tokens, P_NORMAL, 0, code);
   printASTList(*AST);
   List* namespace = malloc(sizeof(List));
   listInit(namespace);
   printf("----------------------------\n");
   executeAST(*AST, namespace);
}
