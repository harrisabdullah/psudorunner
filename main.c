#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"

int main() {
   struct List* tokens = tokenize("OUTPUT 1+1", 10);
   printTokenList(tokens);
   struct List* AST = parse(tokens, 0, NULL_TYPE);
   printASTList(AST);
   executeAST(AST, listInit(Variable));
}
