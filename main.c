#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"

int main() {
    struct List* tokens = tokenize("test <- 1+1", 11);
    printTokenList(tokens);
    struct List* ast = parse(tokens);
    printASTList(ast);
}
