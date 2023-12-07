//
// Created by Harris on 20/11/2023.
//

#include "Tokenizer.h"
#include "TokensList.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// helper function
/**
 * Checks if a specified keyword matches a substring in a given code.
 *
 * @param keyword: Pointer to the keyword to be checked.
 * @param keywordLen: Length of the keyword.
 * @param code: Pointer to the code string.
 * @param currantCodeIndex: Current index in the code string to start matching.
 * @param codeLen: Total length of the code string.
 *
 * @return: Returns 1 if the keyword is found at the specified position in the code,
 *          Returns 0 if the keyword is not found or if the specified position is invalid.
 */
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

// tokenize text unit
/**
 * Tokenizes a single character and appends the corresponding token to the given list of tokens.
 *
 * @param Char: The character to be tokenized.
 * @param tokens: Pointer to a struct TokenList, representing the list of tokens.
 *               The function appends the newly created token to this list.
 */
int tokenizeOneChar(char Char, struct TokenList* tokens){
    struct Token* previousToken = tokenListGetPrevious(tokens);

    switch (Char) {
        case '+':
            tokenListAppend(tokens, (struct Token)
                    {.type=ADDITION,
                     .lexeme=""});
            return 1;

        case '-':
            tokenListAppend(tokens, (struct Token)
                    {.type=SUBTRACTION,
                     .lexeme=""});
            return 1;

        case '/':
            tokenListAppend(tokens, (struct Token)
                {.type=DIVISION,
                 .lexeme=""});
            return 1;

        case '*':
            tokenListAppend(tokens, (struct Token)
                    {.type=MULTIPLICATION,
                     .lexeme=""});
            return 1;

        case '(':
            tokenListAppend(tokens, (struct Token)
                    {.type=OPEN_PAREN,
                     .lexeme=""});
            return 1;

        case ')':
            tokenListAppend(tokens, (struct Token)
                    {.type=CLOSE_PAREN,
                     .lexeme=""});
            return 1;

        case '\n':
            if (previousToken != NULL){
                if (previousToken->type != NEW_LINE){
                    tokenListAppend(tokens, (struct Token)
                            {.type=NEW_LINE,
                             .lexeme=""});
                    return 1;
                }
            }

        default:
            return 0;
    }
};

/**
 * Tokenizes keywords in the given code snippet.
 *
 * @param code The input code snippet to be tokenized.
 * @param currantCodeIndex The current index in the code snippet for processing.
 * @param codeLen The length of the code snippet.
 * @param tokens Pointer to the TokenList structure where tokens will be stored.
 *
 * @return The number of characters consumed to tokenize the keyword, or -1 if no keyword is matched.
 */
int tokenizeKeywords(const char* code, int currantCodeIndex, int codeLen, struct TokenList* tokens){
    if (isKeyword("DECLARE", 7, code, currantCodeIndex, codeLen)){
        tokenListAppend(tokens, (struct Token){
            .type=DECLARE,
            .lexeme=""});
        return 7;
    }

    if (isKeyword("INTEGER", 7, code, currantCodeIndex, codeLen)){
        tokenListAppend(tokens, (struct Token){
                .type=INTEGER,
                .lexeme=""});
        return 7;
    }

    if (isKeyword("REAL", 4, code, currantCodeIndex, codeLen)){
        tokenListAppend(tokens, (struct Token){
                .type=REAL,
                .lexeme=""});
        return 4;
    }

    if (isKeyword("<-", 2, code, currantCodeIndex, codeLen)){
        tokenListAppend(tokens, (struct Token){
                .type=ASSIGNMENT,
                .lexeme=""});
        return 2;
    }

    return -1;
};

/**
 * Tokenizes a number in the given code snippet.
 *
 * @param code The input code snippet to be tokenized.
 * @param currentCodeIndex The current index in the code snippet for processing.
 * @param codeLen The length of the code snippet.
 * @param tokens Pointer to the TokenList structure where tokens will be stored.
 *
 * @return The number of characters consumed to tokenize the number, or -1 if the character at the current index is not a digit.
 */
int tokenizeNumber(const char* code, int currentCodeIndex, int codeLen, struct TokenList* tokens){
    if (!isdigit(code[currentCodeIndex])) {
        return -1;
    }

    int i = currentCodeIndex + 1;
    int isInt = 0;

    while (i<codeLen && (isdigit(code[i]) || code[i] == '.')){
        if (code[i] == '.' && isInt == 0){
            isInt = 1;
        }
        else if (code[i] == '.' && isInt == 1){
            perror("Syntax Error: real contain two '.''s");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char *lexeme = (char *)malloc(lexemeLen + 1);
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    tokenListAppend(tokens, (struct Token) {
        .type = isInt? INTEGER:REAL,
        .lexeme = lexeme
    });
    return lexemeLen;
};

/**
 * Tokenizes an identifier in the given code snippet.
 *
 * @param code The input code snippet to be tokenized.
 * @param currentCodeIndex The current index in the code snippet for processing.
 * @param codeLen The length of the code snippet.
 * @param tokens Pointer to the TokenList structure where tokens will be stored.
 *
 * @return The number of characters consumed to tokenize the identifier, or -1 if the character at the current index is not a valid start for an identifier.
 */
int tokenizeIdentifier(const char* code, int currentCodeIndex, int codeLen, struct TokenList* tokens){
    if (!isalpha(code[currentCodeIndex]) && code[currentCodeIndex] != '_' && code[currentCodeIndex] != '-'){
        return -1;
    }
    int i = currentCodeIndex + 1;

    while (i < codeLen && (isalpha(code[i]) || isdigit(code[i]) || code[i] == '_' || code[i] == '-')){
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char *lexeme = (char *)malloc(lexemeLen + 1);
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    tokenListAppend(tokens, (struct Token){
        .type=IDENTIFIER,
        .lexeme=lexeme
    });

    return lexemeLen;
};

// main tokenizer function
/**
 * Tokenizes a code snippet, identifying and categorizing individual tokens.
 *
 * @param code The input code snippet to be tokenized.
 * @param codeLen The length of the code snippet.
 *
 * @return A dynamically allocated TokenList structure containing the identified tokens.
 *         It is the responsibility of the caller to free the memory when done using the TokenList.
 */
struct TokenList* tokenize(char* code, int codeLen){
    struct TokenList* tokens = tokenListInit();

    for (int i = 0; i < codeLen; i++){
        if (tokenizeOneChar(code[i], tokens)){
            continue;
        };

        int keywordLen = tokenizeKeywords(code, i, codeLen, tokens);
        if (keywordLen != -1){
            i += keywordLen-1;
            continue;
        }

        int numLen = tokenizeNumber(code, i, codeLen, tokens);
        if (numLen != -1){
            i += numLen-1;
            continue;
        }

        int identifierLen = tokenizeIdentifier(code, i, codeLen, tokens);
        if (identifierLen != -1){
            i += identifierLen-1;
            continue;
        }
    }

    return tokens;
};

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
void printToken(struct Token token){
    printf("Token Type: %s\n", tokenTypeToString(token.type));
    printf("Lexeme: %s\n", token.lexeme);
    printf("---------------------------\n");
};