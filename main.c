#include <stdio.h>
#include "Tokenisation/Tokenizer.h"

int main() {
    struct Token* tokens = tokenize("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", 2);
    printf("%s", tokens[0].lexeme);
}
