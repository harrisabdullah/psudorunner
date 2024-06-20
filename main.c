#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"

int main() {
   struct List* tokens = tokenize("OUTPUT (1=1 OR 1=2) AND 1=1", 27); // "OUTUPT (1 < 2 OR 1 = 2) AND 3 <= 7"
   printTokenList(tokens);
   struct List* AST = parse(tokens, 0, NULL_TYPE);
   printASTList(AST);
   executeAST(AST, listInit(Variable));
}
