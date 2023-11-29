#include <stdio.h>
#include "Tokenisation/Tokenizer.h"

int main() {
    struct TokenArray tokens = tokenize("DECLARE Number 1.0+1+2/2<-33.344 test_name-1", 44);
    printTokenArray(tokens);
}
