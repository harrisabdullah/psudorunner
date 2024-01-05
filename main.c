#include <stdio.h>
#include "Tokenisation/Tokenizer.h"
#include "common/List.h"

int main() {
    struct List* tokens = tokenize("TK_DECLARE Number 1.0+1+2/2<-33.344 test_name-1", 44);
    printTokenList(tokens);
}
