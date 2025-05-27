#include "std.h"

int STD_FUNC_COUNT = 1;
const char* STD_FUNC_IDENTIFIERS[] = {"INTEGER_IDENTIFIER"};
void (*STD_FUNCS[])(List, struct Stack*, List*) = {&std_INT};
