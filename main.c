#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"

int main() {
    struct List* tokens = tokenize("DECLARE i: BOOLEAN\ni <- TRUE\nOUTPUT i", 37);
    // printTokenList(tokens);
    struct List* ast = parse(tokens);
    // printASTList(ast);
    executeAST(ast);
}
