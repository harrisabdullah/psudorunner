//
// Created by Harris on 04/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_TOKEN_H
#define PSUDO_INTERPRATOR_2_TOKEN_H

enum TokenType {
    TK_DECLARE, // TK_DECLARE statement e.g. "TK_DECLARE i: TK_INTEGER"
    TK_IDENTIFIER, // names of function or variables e.g. `i`
    TK_INTEGER_IDENTIFIER, // the integer type e.g. the "TK_INTEGER" in "TK_DECLARE i: TK_INTEGER"
    TK_REAL_IDENTIFIER, // the real type
    TK_INTEGER, // integer values e.g. "1", "23", "-444"
    TK_REAL, // real values e.g. "1.1", "-23.0", "22.22"
    TK_ASSIGNMENT, // the assignment operator e.g. the "<-" in "i <- 5"
    TK_ADDITION, // the addition operator e.g. "1+1"
    TK_SUBTRACTION, // the subtraction operator e.g. "2-1"
    TK_DIVISION, // the division operator e.g. "4/2"
    TK_MULTIPLICATION, // the multiplication operator e.g. "3*3"
    TK_OPEN_PAREN, // open parenthesis
    TK_CLOSE_PAREN, // close parenthesis
    TK_NEW_LINE, // used to terminate statements e.g. the semicolon in c
};

struct Token {
    enum TokenType type;
    char* lexeme; // TODO: consider using linked list or something similar
};

#endif //PSUDO_INTERPRATOR_2_TOKEN_H
