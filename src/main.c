#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"
#include <stdio.h>
#include <string.h>

int main() {
   char* code = "OUTPUT \"Hello world!\"";
   List tokens = tokenize(code, strlen(code));

   printf("-------- DEBUG info --------\nTokens: ");
   printTokenList(tokens);
   List* AST = malloc(sizeof(List));
   listInit(AST);
   parse(AST, tokens, P_NORMAL, 0, code);
   printf("\nAST: ");
   printASTList(*AST);
   List* namespace = malloc(sizeof(List));
   listInit(namespace);
   printf("\n------ program output ------\n");
   executeAST(*AST, namespace);
}
