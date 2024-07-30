#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"

int main() {
   struct List* tokens = tokenize("DECLARE i:INTEGER\nFOR i <- 1 TO 10\nOUTPUT i\nNEXT i", 50);
   printTokenList(tokens);
   struct List* AST = listInit(ASTNode);
   parse(tokens, AST, P_NORMAL, 0);
   printASTList(AST);
   executeAST(AST, listInit(Variable));
}
