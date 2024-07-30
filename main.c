#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"

int main() {
   struct List* tokens = tokenize("DECLARE i: INTEGER\ni <- 0\nREPEAT\ni <- i + 1\nOUTPUT i\nUNTIL i > 10", 65);
   printTokenList(tokens);
   struct List* AST = listInit(ASTNode);
   parse(tokens, AST, P_NORMAL, 0);
   printASTList(AST);
   executeAST(AST, listInit(Variable));
}
