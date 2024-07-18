#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"

int main() {
   // TODO: test IF and ELSE please
   struct List* tokens = tokenize("IF FALSE THEN\nOUTPUT 1\nELSE\nOUTPUT 2\nENDIF\nOUTPUT 3\n", 52);
   printTokenList(tokens);
   struct List* AST = listInit(ASTNode);
   parse(tokens, AST, P_NORMAL, 0);
   printASTList(AST);
   executeAST(AST, listInit(Variable));
}
