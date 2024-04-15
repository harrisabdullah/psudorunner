#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"

int main() {
    struct List* tokens = tokenize("DECLARE i: INTEGER\nDECLARE j: REAL\ni <- 10\nj <- i * 1.2\nOUTPUT j\nOUTPUT i", 73);
    // printTokenList(tokens);
    struct List* ast = parse(tokens);
    // printASTList(ast);
    executeAST(ast);
}
