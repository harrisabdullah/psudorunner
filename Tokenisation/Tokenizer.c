//
// Created by Harris on 20/11/2023.
//

#include "Token.h"
#include "../common/List.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

/**
 * Tokenizes a single character and appends the corresponding token to the given list of tokens.
 *
 * @param Char: The character to be tokenized.
 * @param tokens: Pointer to a struct TokenList, representing the list of tokens.
 *               The function appends the newly created token to this list.
 */
int tokenizeOneChar(char Char, struct List* tokens) {

    union listValue* previousToken = NULL;
    if (tokens->head != 0){
        previousToken = listGetLastItem(tokens);
    }

    switch (Char) {
        case '+':
            listAppend(tokens, (union listValue){.token = (struct Token){.type = ADDITION, .lexeme = ""}});
            return 1;

        case '-':
            listAppend(tokens, (union listValue){.token = (struct Token){.type = SUBTRACTION, .lexeme = ""}});
            return 1;

        case '/':
            listAppend(tokens, (union listValue){.token = (struct Token){.type = DIVISION, .lexeme = ""}});
            return 1;

        case '*':
            listAppend(tokens, (union listValue){.token = (struct Token){.type = MULTIPLICATION, .lexeme = ""}});
            return 1;

        case '(':
            listAppend(tokens, (union listValue){.token = (struct Token){.type = OPEN_PAREN, .lexeme = ""}});
            return 1;

        case ')':
            listAppend(tokens, (union listValue){.token = (struct Token){.type = CLOSE_PAREN, .lexeme = ""}});
            return 1;

        case '\n':
            if (previousToken != NULL) {
                struct Token* prevToken = &previousToken->token;
                if (prevToken->type != NEW_LINE) {
                    listAppend(tokens, (union listValue){.token = (struct Token){.type = NEW_LINE, .lexeme = ""}});
                    return 1;
                }
            }

        default:
            return 0;
    }
}

/**
Extracts and tokenizes keywords from the given code snippet.
*
* @param code The input code snippet to be processed.
* @param currentCodeIndex The current index in the code snippet for processing.
* @param codeLen The length of the code snippet.
* @param tokens Pointer to the TokenList structure where tokens will be stored.
*
* @return The number of characters consumed to tokenize the keyword, or -1 if no keyword is found.
*/
int tokenizeKeywords(const char* code, int currentCodeIndex, int codeLen, struct List* tokens) {
    if (isKeyword("DECLARE", 7, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .token = {
                        .type = DECLARE,
                        .lexeme = ""
                }
        });
        return 7;
    }

    if (isKeyword("INTEGER", 7, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .token = {
                        .type = INTEGER,
                        .lexeme = ""
                }
        });
        return 7;
    }

    if (isKeyword("REAL", 4, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .token = {
                        .type = REAL,
                        .lexeme = ""
                }
        });
        return 4;
    }

    if (isKeyword("<-", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .token = {
                        .type = ASSIGNMENT,
                        .lexeme = ""
                }
        });
        return 2;
    }

    return -1;
}
/**
* Extracts and tokenizes a numeric literal from the given code snippet.
*
* @param code The input code snippet to be processed.
* @param currentCodeIndex The current index in the code snippet for processing.
* @param codeLen The length of the code snippet.
* @param tokens Pointer to the TokenList structure where tokens will be stored.

* @return The number of characters consumed to tokenize the numeric literal, or -1 if the character at the current index is not a digit.
*/
int tokenizeNumber(const char* code, int currentCodeIndex, int codeLen, struct List* tokens) {
    if (!isdigit(code[currentCodeIndex])) {
        return -1;
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
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    // Assuming tokens is a list of Token
    listAppend(tokens, (union listValue) {
            .token = {
                    .type = isInt ? INTEGER : REAL,
                    .lexeme = lexeme
            }
    });

    return lexemeLen;
}

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
int tokenizeIdentifier(const char* code, int currentCodeIndex, int codeLen, struct List* tokens) {
    if (!isalpha(code[currentCodeIndex]) && code[currentCodeIndex] != '_' && code[currentCodeIndex] != '-') {
        return -1;
    }

    int i = currentCodeIndex + 1;

    while (i < codeLen && (isalpha(code[i]) || isdigit(code[i]) || code[i] == '_' || code[i] == '-')) {
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char* lexeme = (char*)malloc(lexemeLen + 1);
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    // Create a union listValue with a struct Token and set its values
    union listValue tokenValue;
    tokenValue.token.type = IDENTIFIER;
    tokenValue.token.lexeme = lexeme;

    // Append the token to the list
    listAppend(tokens, tokenValue);

    return lexemeLen;
}

/**
 * Tokenizes a code string, identifying and categorizing individual tokens.
 *
 * @param code The input code string to be tokenized.
 * @param codeLen The length of the code string.
 *
 * @return A dynamically allocated TokenList structure containing the identified tokens.
 *         It is the responsibility of the caller to free the memory when done using the TokenList.
 */
struct List* tokenize(char* code, int codeLen) {
    struct List* tokens = listInit(TOKEN);

    for (int i = 0; i < codeLen; i++) {
        if (tokenizeOneChar(code[i], tokens)) {
            continue;
        }

        int keywordLen = tokenizeKeywords(code, i, codeLen, tokens);
        if (keywordLen != -1) {
            i += keywordLen - 1;
            continue;
        }

        int numLen = tokenizeNumber(code, i, codeLen, tokens);
        if (numLen != -1) {
            i += numLen - 1;
            continue;
        }

        int identifierLen = tokenizeIdentifier(code, i, codeLen, tokens);
        if (identifierLen != -1) {
            i += identifierLen - 1;
            continue;
        }
    }

    return tokens;
}


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

/**
 * Print the content of a Token structure including the Type and Lexeme.
 *
 * @param token the token to be printed.
 */
void printToken(struct Token token){
    printf("Token Type: %s\n", tokenTypeToString(token.type));
    printf("Lexeme: %s\n", token.lexeme);
    printf("---------------------------\n");
};

/**
 * Prints the content of a given List of tokens.
 *
 * @param tokens: A pointer the the list to be printed.
 */
void printTokenList(struct List* tokens){
    for (int i = 0; i<tokens->head; i++){
        printToken(tokens->array[i].token);
    }
};