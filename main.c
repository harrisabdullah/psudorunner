#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"

int main() {
    struct List* tokens = tokenize("test <- 1+1/1", 15-2);
    printTokenList(tokens);
    struct List* ast = parse(tokens);
    printASTList(ast);
}
