#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"

int main() {
    struct List* tokens = tokenize("OUTPUT 1 = 2", 12);
    // printTokenList(tokens);
    struct List* ast = parse(tokens);
    // printASTList(ast);
    executeAST(ast);
}
