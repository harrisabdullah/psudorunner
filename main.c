#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "testing/testTokenizer.h"
#include "common/tokenTypeToString.h"

int main() {
   struct List* tokens = tokenize("OUTPUT TRUE AND 2 < 3 OR 3+3 < 44", 33);
   // printTokenList(tokens);
   struct List* AST = parse(tokens, 0, NULL_TYPE);
   // printASTList(AST);
   executeAST(AST, listInit(Variable));
}
