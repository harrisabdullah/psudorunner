//
// Created by Harris on 04/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_TOKEN_H
#define PSUDO_INTERPRATOR_2_TOKEN_H

enum TokenType {
    NULL_TYPE = -1,
    DECLARE, // DECLARE statement e.g. "DECLARE i: INTEGER"
    IDENTIFIER, // names of function or variables e.g. `i`
    INTEGER_IDENTIFIER, // the integer type e.g. the "INTEGER" in "DECLARE i: INTEGER"
    REAL_IDENTIFIER, // the real type
    BOOLEAN_IDENTIFIER,
    STRING_IDENTIFIER,
    INTEGER, // declaring integer values
    REAL, // declaring real values
    BOOLEAN, // declaring boolean values
    STRING,
    ASSIGNMENT, // the assignment operator e.g. the "<-" in "i <- 5"
    ADDITION, // the addition operator e.g. "1+1"
    SUBTRACTION, // the subtraction operator e.g. "2-1"
    DIVISION, // the division operator e.g. "4/2"
    MULTIPLICATION, // the multiplication operator e.g. "3*3"
    MODULO,
    EQUALS,
    NOT_EQUALS,
    GREATER,
    LESSER,
    GREATER_OR_EQUALS,
    LESSER_OR_EQUALS,
    AND,
    OR,
    NOT,
    OPEN_PAREN, // open parenthesis
    CLOSE_PAREN, // close parenthesis
    COLON, // colon
    NEW_LINE, // used to terminate statements e.g. the semicolon in c
    OUTPUT, // its basically print
    IF,
    THEN,
    ENDIF,
    ELSE,
    WHILE,
    ENDWHILE,
    REPEAT,
    UNTIL,
    FOR,
    TO,
    NEXT,
    OPEN_SQUARE_PAREN,
    CLOSE_SQUARE_PAREN,
    CHARACTER,
};

typedef struct Token {
    enum TokenType type;
    char* lexeme;
} Token;

#endif //PSUDO_INTERPRATOR_2_TOKEN_H
