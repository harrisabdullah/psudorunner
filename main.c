#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"

int main() {
    struct List* tokens = tokenize("IF TRUE THEN\nOUTPUT 1\nENDIF\nOUTPUT 2", 36);
    struct List* ast = parse(tokens, -1, -1);
    printASTList(ast);
    executeAST(ast, listInit(Variable));
}
