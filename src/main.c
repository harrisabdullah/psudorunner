#include "Tokenisation/Tokenizer.h"
#include "Parser/Parser.h"
#include "common/List.h"
#include "ExecutionEngine/ExecutionEngine.h"
#include "common/tokenTypeToString.h"
#include <stdio.h>
#include <string.h>

int main() {
   char* code = "OUTPUT \"Hello world!\"";

   // char* code =
   // "IF 5 > 3 THEN\n"
   // "    OUTPUT \"Yes\"\n"
   // "ELSE\n"
   // "    OUTPUT \"No\"\n"
   // "ENDIF\n";

   // char* code =
   // "FOR i = 1 TO 5\n"
   // "    OUTPUT i\n"
   // "NEXT i\n";

   // char* code =
   // "DECLARE x: INTEGER\n"
   // "x <- 1\n"
   // "WHILE x <= 3 DO\n"
   // "    OUTPUT x\n"
   // "    x <- x + 1\n"
   // "ENDWHILE\n";

// char* code =
//    "DECLARE n: INTEGER\n"
//    "FOR n = 1 TO 10\n"
//    "    IF n MOD 2 = 0 THEN\n"
//    "        OUTPUT n\n"
//    "    ENDIF\n"
//    "NEXT n\n";

   List tokens = tokenize(code, strlen(code));

   printf("-------- DEBUG info --------\nTokens: ");
   printTokenList(tokens);
   List* AST = malloc(sizeof(List));
   listInit(AST);
   parse(AST, tokens, P_NORMAL, 0, code);
   printf("\nAST: ");
   printASTList(*AST);
   List* namespace = malloc(sizeof(List));
   listInit(namespace);
   printf("\n------ program output ------\n");
   executeAST(*AST, namespace);
}
