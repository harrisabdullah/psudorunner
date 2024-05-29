#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "testing/testTokenizer.h"

int main() {
   struct List* tokens = tokenize("DECLARE a: INTEGER\na <- 3*3\nIF a < 10 THEN\nOUTPUT a+1\nOUTPUT 12\nENDIF\nOUTPUT a", 78);
   struct List* AST = parse(tokens, 0, NULL_TYPE);
   executeAST(AST, listInit(Variable));
}
