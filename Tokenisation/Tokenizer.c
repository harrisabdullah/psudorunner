//
// Created by Harris on 20/11/2023.
//

#include "Token.h"
#include "../common/List.h"
#include "../common/tokenTypeToString.h"
#include "../errors/internalErrors.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int tokenizeOneChar(Token* token, Token* previousToken, char Char) {
    switch (Char) {
        case '+':
            token->type = ADDITION;
            break;

        case '-':
            token->type = SUBTRACTION;
            break;

        case '/':
            token->type = DIVISION;
            break;

        case '*':
            token->type = MULTIPLICATION;
            break;

        case '(':
            token->type = OPEN_PAREN;
            break;

        case ')':
            token->type = CLOSE_PAREN;
            break;

        case ':':
            token->type = COLON;
            break;

        case '=':
            token->type = EQUALS;
            break;

        case '<':
            token->type = LESSER;
            break;

        case '>':
            token->type = GREATER;
            break;

        case '[':
            token->type = OPEN_SQUARE_PAREN;
            break;

        case ',':
            token->type = COMMA;
            break;
            
        case ']':
            token->type = CLOSE_SQUARE_PAREN;
            break;

        case '\n':
            token->type = NEW_LINE;
            break;


        default:
            return 0;
    }
    token->lexeme = "";
    return 1;
}


int tokenizeKeywords(Token* token, const char* code, int currentCodeIndex, int codeLen) {
    int KEYWORD_COUNT = 25;
    char* KEYWORDS_STR[] = {"IF", "ELSE",  "THEN", "ENDIF", "<-", "<>", "MOD", "<=", ">=", "OR", "AND", "NOT",
                            "BOOLEAN", "INTEGER", "REAL", "STRING", "OUTPUT", "DECLARE", "WHILE", "ENDWHILE", 
                            "REPEAT", "UNTIL", "FOR", "TO", "NEXT"};
    enum TokenType KEYWORD_TYPE[] = {IF, ELSE, THEN, ENDIF, ASSIGNMENT, NOT_EQUALS, MODULO, LESSER_OR_EQUALS, GREATER_OR_EQUALS, OR, AND, NOT,
                                    BOOLEAN_IDENTIFIER, INTEGER_IDENTIFIER, REAL_IDENTIFIER, STRING_IDENTIFIER, OUTPUT, DECLARE, WHILE, ENDWHILE,
                                    REPEAT, UNTIL, FOR, TO, NEXT};
    int kwLen;

    for (int i=0; i<KEYWORD_COUNT; i++){
        kwLen = strlen(KEYWORDS_STR[i]);
        if (kwLen + currentCodeIndex > codeLen){
            continue;
        }
        if (currentCodeIndex == 9){
        }
        if (strncmp(KEYWORDS_STR[i], &code[currentCodeIndex], kwLen) == 0){
            token->type = KEYWORD_TYPE[i];
            token->lexeme = "";
            return kwLen;
        }
    }

    return 0;
}


int tokenizeBool(Token* token, const char* code, int currentCodeIndex, int codeLen){
    if (currentCodeIndex + 4 >= codeLen){
       return 0;
    }
    if (strncmp("TRUE", &code[currentCodeIndex], 4) == 0){
        token->type = BOOLEAN;
        token->lexeme = "TRUE";
        return 4;
    }
    if (currentCodeIndex + 5 >= codeLen){
        return 0;
    }
    if (strncmp("FALSE", &code[currentCodeIndex], 5) == 0){
        token->type = BOOLEAN;
        token->lexeme = "FALSE";
        return 5;
    }
    return 0;
}


int tokenizeNumber(Token* token, const char* code, int currentCodeIndex, int codeLen) {
    if (!isdigit(code[currentCodeIndex])) {
        return 0;
    }

    int i = currentCodeIndex + 1;
    int isInt = 1;

    while (i < codeLen && (isdigit(code[i]) || code[i] == '.')) {
        if (code[i] == '.' && isInt == 1) {
            isInt = 0;
        } else if (code[i] == '.' && isInt == 0) {
            perror("Syntax Error: number contains two '.'s");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char* lexeme = (char*)malloc(lexemeLen + 1);
    if (lexeme == NULL)
        ie_allocationError();
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    token->type = isInt ? INTEGER : REAL;
    token->lexeme = lexeme;

    return lexemeLen;
}


int tokenizeIdentifier(Token* token, const char* code, int currentCodeIndex, int codeLen) {
    if (!isalpha(code[currentCodeIndex])) {
        return 0;
    }

    int i = currentCodeIndex + 1;

    while (i < codeLen && (isalpha(code[i]) || isdigit(code[i]) || code[i] == '_')) {
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char* lexeme = (char*)malloc(lexemeLen + 1);
    if (lexeme == NULL)
        ie_allocationError();
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    token->type = IDENTIFIER;
    token->lexeme = lexeme;

    return lexemeLen;
}

int tokenizeString(Token* token, const char* code, int currentCodeIndex, int codeLen) {
    if (code[currentCodeIndex] != '"'){
        return 0;
    }

    int i = currentCodeIndex + 1;
    while (code[i] != '"'){
        if (code[i] == '\\'){
            i++;
        }
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char* lexeme = (char*)malloc(lexemeLen);
    strncpy(lexeme, code + currentCodeIndex + 1, lexemeLen - 1);
    lexeme[lexemeLen - 1] = '\0';

    token->type = STRING;
    token->lexeme = lexeme;

    return lexemeLen + 1;
}


List tokenize(char* code, int codeLen) {
    int lexemeLen = 0;
    int lineNumber = 1;
    List tokens;
    listInit(&tokens);
    Token* previouseToken = NULL;
    Token* newToken = (Token*)malloc(sizeof(Token));
    if (newToken == NULL)
        ie_allocationError();

    for (int i = 0; i < codeLen; i++) {
        lexemeLen = tokenizeOneChar(newToken, previouseToken, code[i]);
        if (lexemeLen == 0)
            lexemeLen = tokenizeKeywords(newToken, code, i, codeLen);
        if (lexemeLen == 0)
            lexemeLen = tokenizeNumber(newToken, code, i, codeLen);
        if (lexemeLen == 0)
            lexemeLen = tokenizeIdentifier(newToken, code, i, codeLen);
        if (lexemeLen == 0)
            lexemeLen = tokenizeString(newToken, code, i, codeLen);
        if (lexemeLen == 0)
            lexemeLen = tokenizeBool(newToken, code, i, codeLen);
        if (lexemeLen == 0){
            continue;
        }

        listAppend(&tokens, newToken);
        previouseToken = newToken;
        newToken = (Token*)malloc(sizeof(Token));
        if (newToken == NULL)
            ie_allocationError(); 
        i += lexemeLen - 1;
        lexemeLen = 0;
    }

    return tokens;
}

void printToken(Token* token){
    if (token->lexeme[0] == '\0'){
        printf("%s", tokenTypeToString(token->type));
        return;
    }
    printf("%s: '%s'", tokenTypeToString(token->type), token->lexeme);
};

void printTokenList(List tokens){
    printf("{");
    for (int i = 0; i<tokens.length; i++){
        printf("%i: ", i);
        printToken(tokens.items[i]);
        printf(", ");
    }
    printf("}\n");
};
