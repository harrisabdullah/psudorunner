//
// Created by Harris on 04/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_TOKEN_H
#define PSUDO_INTERPRATOR_2_TOKEN_H

enum TokenType {
    NULL_TYPE = -1,
    DECLARE, 
    IDENTIFIER, 
    // ALL TYPE IDENTIFERS MUST BE ADDED TO isTypeIdentifier() IN Parser.c
    INTEGER_IDENTIFIER,
    REAL_IDENTIFIER, 
    BOOLEAN_IDENTIFIER,
    STRING_IDENTIFIER,
    // ALL TYPE IDENTIFERS MUST BE ADDED TO isTypeIdentifier() IN Parser.c
    INTEGER, 
    REAL,
    BOOLEAN, 
    STRING,
    ASSIGNMENT, 
    ADDITION,
    SUBTRACTION, 
    DIVISION, 
    MULTIPLICATION, 
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
    OPEN_PAREN, 
    CLOSE_PAREN,
    COLON,
    NEW_LINE,
    OUTPUT,
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
    COMMA,
    FUNCTION_CALL,
};

typedef struct Token {
    enum TokenType type;
    char* lexeme;
} Token;

#endif //PSUDO_INTERPRATOR_2_TOKEN_H
