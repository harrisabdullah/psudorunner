#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"
#include <stdio.h>

int main() {
   List tokens = tokenize("OUTPUT 1", 8);
   printTokenList(tokens);
    List* AST = malloc(sizeof(List));
   listInit(AST);
   parse(AST, tokens, P_NORMAL, 0);
   printASTList(*AST);
   List* namespace = malloc(sizeof(List));
   listInit(namespace);
   executeAST(*AST, namespace);
}
