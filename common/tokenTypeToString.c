//
// Created by Harris on 27/03/2024.
//

#include "tokenTypeToString.h"
#include "../Tokenisation/Token.h"


// debug function
/**
 * Converts a TokenType enum value to its corresponding string representation.
 *
 * @param token The TokenType enum value to be converted.
 *
 * @return A string representing the TokenType, or "UNKNOWN_TOKEN" if the TokenType is not recognized.
 */
const char* tokenTypeToString(enum TokenType token) {
    switch (token) {
        case NULL_TYPE:
            return "NULL_TYPE";
        case DECLARE:
            return "DECLARE";
        case IDENTIFIER:
            return "IDENTIFIER";
        case INTEGER_IDENTIFIER:
            return "INTEGER_IDENTIFIER";
        case REAL_IDENTIFIER:
            return "REAL_IDENTIFIER";
        case INTEGER:
            return "INTEGER";
        case REAL:
            return "REAL";
        case ASSIGNMENT:
            return "ASSIGNMENT";
        case ADDITION:
            return " ('+') ";
        case SUBTRACTION:
            return " ('-') ";
        case DIVISION:
            return " ('/') ";
        case MULTIPLICATION:
            return " ('*') ";
        case OPEN_PAREN:
            return " ('(') ";
        case CLOSE_PAREN:
            return " (')') ";
        case NEW_LINE:
            return "NEW_LINE";
        case COLON:
            return "COLON";
        case OUTPUT:
            return "OUTPUT";
        case BOOLEAN:
            return "BOOLEAN";
        case EQUALS:
            return "EQUALS";
        case IF:
            return "IF";
        case ENDIF:
            return "ENDIF";
        case THEN:
            return "THEN";
        case GREATER:
            return " ('>') ";
        case LESSER:
            return " ('<') ";
        case LESSER_OR_EQUALS:
            return " ('<=') ";
        case GREATER_OR_EQUALS:
            return " ('>=') ";
        case AND:
            return "AND";
        case NOT:
            return "NOT";
        case OR:
            return "OR";
        case BOOLEAN_IDENTIFIER:
            return "BOOLEAN_IDENTIFIER";
        case NOT_EQUALS:
            return " ('!=') ";
    }
}
