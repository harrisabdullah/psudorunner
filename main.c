#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"

int main() {
    struct List* tokens = tokenize("OUTPUT NOT 1/2 < 3", 18);
    struct List* ast = parse(tokens, -1, -1);
    printASTList(ast);
    executeAST(ast, listInit(Variable));
}
