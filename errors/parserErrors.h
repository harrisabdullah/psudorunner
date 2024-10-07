//
// Created by Harris on 13/09/2024.
//

#ifndef PSUDO_INTERPRATOR_2_PARSER_ERRORS_H
#define PSUDO_INTERPRATOR_2_PARSER_ERRORS_H

void pe_syntaxError(int line, char* sourceCode, char* message);
void pe_forError(int line, char* sourceCode, char* message);
void pe_ifError(int line, char* sourceCode, char* message);
void pe_elseError(int line, char* sourceCode, char* message);
void pe_declareError(int line, char* sourceCode, char* message);
void pe_assignmentError(int line, char* sourceCode, char* message);

#endif // PSUDO_INTERPRATOR_2_PARSER_ERRORS_H