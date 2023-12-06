//
// Created by Harris on 20/11/2023.
//

#include "Tokenizer.h"
#include "TokensList.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void tokenizeOneChar(char Char, struct TokenList* tokens){
    struct Token* previousToken = getPrevious(tokens);

    switch (Char) {
        case '+':
            tokenListAppend(tokens, (struct Token)
                    {.type=ADDITION,
                     .lexeme=NULL});
            return;

        case '-':
            tokenListAppend(tokens, (struct Token)
                    {.type=SUBTRACTION,
                     .lexeme=NULL});
            return;

        case '/':
            tokenListAppend(tokens, (struct Token)
                {.type=DIVISION,
                 .lexeme=NULL});
            return;

        case '*':
            tokenListAppend(tokens, (struct Token)
                    {.type=MULTIPLICATION,
                     .lexeme=NULL});
            return;

        case '(':
            tokenListAppend(tokens, (struct Token)
                    {.type=OPEN_PAREN,
                     .lexeme=NULL});
            return;

        case ')':
            tokenListAppend(tokens, (struct Token)
                    {.type=CLOSE_PAREN,
                     .lexeme=NULL});
            return;

        case '\n':
            if (previousToken != NULL){
                if (previousToken->type != NEW_LINE){
                    tokenListAppend(tokens, (struct Token)
                            {.type=NEW_LINE,
                             .lexeme=NULL});
                    return;
                }
            }

        default:
            return;
    }
};

int isKeyword(const char* keyword, int keywordLen, const char* code, int currantCodeIndex, int codeLen){
    if (keywordLen+currantCodeIndex > codeLen){
        return 0;
    }
    for (int i=0; i<keywordLen; i++){
        if (keyword[i] != code[currantCodeIndex+i]){
            return 0;
        }
    }
    return 1;
};

void tokenizeKeywords(const char* code, int currantCodeIndex, int codeLen, struct Token* currantToken){
    if (isKeyword("DECLARE", 7, code, currantCodeIndex, codeLen)){
        currantToken->type = DECLARE;
        currantToken->lexeme = NULL;
        return 7;
    }

    if (isKeyword("INTEGER", 7, code, currantCodeIndex, codeLen)){
        currantToken->type = INTEGER_IDENTIFIER;
        currantToken->lexeme = NULL;
        return 7;
    }

    if (isKeyword("REAL", 4, code, currantCodeIndex, codeLen)){
        currantToken->type = REAL_IDENTIFIER;
        currantToken->lexeme = NULL;
        return 4;
    }

    if (isKeyword("<-", 2, code, currantCodeIndex, codeLen)){
        currantToken->type = ASSIGNMENT;
        currantToken->lexeme = NULL;
        return 2;
    }

    return 0;
};

int tokenizeNumber(const char* code, int currantCodeIndex, int codeLen, struct Token* currantToken){
    if (!isdigit(code[currantCodeIndex])) {
        return 0;
    }

    int isInt = 1;
    int numStringLen = 10;
    char * numString = malloc(numStringLen * sizeof(char));
    numString[0] = code[currantCodeIndex];
    int nextNumIndex = 1;

    for (int j=currantCodeIndex+1; j < codeLen && !isspace(code[j]); j++){
        if ((!isdigit(code[j]) && code[j] != '.')){
            // catches invalid chars
            break;
        } else if (code[j] == '.'){
            if (!isInt){
                // catches two decimal places in a number
                perror("invalid syntax");
                exit(EXIT_FAILURE);
            }
            isInt = 0;
            numString[nextNumIndex] = '.';
            nextNumIndex++;
        } else {
            numString[nextNumIndex] = code[j];
            nextNumIndex++;
        }

        if (nextNumIndex >= numStringLen){
            numStringLen += 10;
            numString = realloc(numString, numStringLen * sizeof(char));

            if (numString == NULL){
                perror("failed to allocate memory");
                exit(EXIT_FAILURE);
            }
        }
    }

    currantToken->type = isInt? INTEGER:REAL;
    currantToken->lexeme = numString;
    currantToken->lexemeLen = nextNumIndex;
    return nextNumIndex;
};

struct TokenArray tokenize(char* code, int codeLen){
    int tokenArraySize = 50;
    int nextTokenIndex = 0;
    struct Token* tokens = malloc(50 * sizeof(struct Token));

    if (tokens == NULL){
        perror("failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < codeLen; i++){

        // tokenize one character
        int isOneChar = tokenizeOneChar(code[i], &tokens[nextTokenIndex], nextTokenIndex == 0 ? NULL : &tokens[nextTokenIndex - 1]);
        if (isOneChar) {
            nextTokenIndex++;
        }
        else {
            // Tokenize keywords
            int keyWordLen = tokenizeKeywords(code, i, codeLen, &tokens[nextTokenIndex]);
            if (keyWordLen != 0) {
                nextTokenIndex++;
                i += keyWordLen - 1;
            }
            else {
                // Tokenize numbers
                int numberLen = tokenizeNumber(code, i, codeLen, &tokens[nextTokenIndex]);
                if (numberLen != 0) {
                    nextTokenIndex++;
                    i += numberLen - 1;
                }
                else {
                    if (isalpha(code[i])){
                        int j = i+1;
                        int lexemeLen = 50;
                        char* lexeme = malloc(sizeof(char) * lexemeLen);
                        lexeme[0] = code[i];
                        int nextLexemeIndex = 1;

                        while(isalpha(code[j]) || isdigit(code[j]) || code[j] == '-' || code[j] == '_'){
                            lexeme[nextLexemeIndex] = code[j];
                            nextLexemeIndex++;
                                j++;

                            if (nextLexemeIndex >= lexemeLen){
                                lexemeLen += 50;
                                    lexeme = realloc(lexeme, lexemeLen * sizeof(char));

                                if (lexeme == NULL){
                                    perror("failed to allocate memory");
                                    exit(EXIT_FAILURE);
                                }
                            }
                        }
                        i += j-i;

                        tokens[nextTokenIndex].type = IDENTIFIER;
                        tokens[nextTokenIndex].lexeme = lexeme;
                        tokens[nextTokenIndex].lexemeLen = nextLexemeIndex;
                        nextTokenIndex++;
                    }
                }
            }
        }

        if (nextTokenIndex >= tokenArraySize){
            tokenArraySize += 50;
            tokens = realloc(tokens, tokenArraySize * sizeof(struct Token));

            if (tokens == NULL){
                perror("failed to allocate memory");
                exit(EXIT_FAILURE);
            }
        }
    }

    struct TokenArray tokenArray = {.tokens = tokens, .len = nextTokenIndex};
    return tokenArray;
};

void printTokenArray(struct TokenArray tokens){
    for (int i = 0; i<tokens.len; i++){
        if (tokens.tokens[i].lexeme != NULL) {
            printf("{%s : \"%s\"}\n", tokenTypeToString(tokens.tokens[i].type), tokens.tokens[i].lexeme);
        } else {
            printf("{%s}\n", tokenTypeToString(tokens.tokens[i].type));
        }
    }
};

const char* tokenTypeToString(enum TokenType token) {
    switch (token) {
        case NULL_TOKEN:
            return "NULL_TOKEN";
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
            return "ADDITION";
        case SUBTRACTION:
            return "SUBTRACTION";
        case DIVISION:
            return "DIVISION";
        case MULTIPLICATION:
            return "MULTIPLICATION";
        case OPEN_PAREN:
            return "OPEN_PAREN";
        case CLOSE_PAREN:
            return "CLOSE_PAREN";
        case NEW_LINE:
            return "NEW_LINE";
        default:
            return "UNKNOWN_TOKEN";
    }
}