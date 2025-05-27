#include "parserErrors.h"
#include "errors.h"

void pe_syntaxError(int line, char* sourceCode, char* message){
   pe_raise(line, sourceCode, "SyntaxError", message, "");
}

void pe_forError(int line, char* sourceCode, char* message){
   pe_raise(line, sourceCode, "SyntaxError", message, "\n\nCorrect format:\n   FOR <name> <- <integer> TO <integer>\n        ...\n    NEXT <name>");
}

void pe_ifError(int line, char* sourceCode, char* message){
   pe_raise(line, sourceCode, "SyntaxError", message, "\n\nCorrect format:\n   IF <condition> THEN\n        ...\n    ENDIF");
}

void pe_elseError(int line, char* sourceCode, char* message){
   pe_raise(line, sourceCode, "SyntaxError", message, "\n\nCorrect format:\n   IF <condition> THEN\n        ...\n    ELSE\n        ...\n    ENDIF");
}

void pe_declareError(int line, char* sourceCode, char* message){
   pe_raise(line, sourceCode, "SyntaxError", message, "\n\nCorrect format:\n   DECLARE <name>: <datatype>");
}

void pe_assignmentError(int line, char* sourceCode, char* message){
   pe_raise(line, sourceCode, "SyntaxError", message, "\n\nCorrect format:\n   <name> <- <value>");
}
