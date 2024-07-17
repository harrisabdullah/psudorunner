//
// Created by Harris on 20/11/2023.
//

#include "Token.h"
#include "../common/List.h"
#include "../common/tokenTypeToString.h"
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
 * Tokenizes a single character and appends the corresponding tokenValue to the given list of tokens.
 *
 * @param Char: The character to be tokenized.
 * @param tokens: Pointer to a struct TokenList, representing the list of tokens.
 *               The function appends the newly created tokenValue to this list.
 */
int tokenizeOneChar(char Char, struct List* tokens) {

    union listValue* previousToken = NULL;
    if (tokens->head != 0){
        previousToken = listGetLastItem(tokens);
    }

    // type of declare is a stand in for NULL as it is impossible for declare to be one character.
    struct Token new_token = {.type=DECLARE, .lexeme=""};

    switch (Char) {
        case '+':
            new_token.type = ADDITION;
            break;

        case '-':
            new_token.type = SUBTRACTION;
            break;

        case '/':
            new_token.type = DIVISION;
            break;

        case '*':
            new_token.type = MULTIPLICATION;
            break;

        case '(':
            new_token.type = OPEN_PAREN;
            break;

        case ')':
            new_token.type = CLOSE_PAREN;
            break;

        case ':':
            new_token.type = COLON;
            break;

        case '=':
            new_token.type = EQUALS;
            break;

        case '<':
            new_token.type = LESSER;
            break;

        case '>':
            new_token.type = GREATER;
            break;

        case '\n':
            if (previousToken != NULL) {
                struct Token* prevToken = &previousToken->tokenValue;
                if (prevToken->type != NEW_LINE) {
                    new_token.type = NEW_LINE;
                    break;
                }
            }

        default:
            return 0;
    }
    listAppend(tokens, (union listValue) new_token);
    return 1;
}

/**
extracts and tokenizes keywords from the given code snippet.
*
* @param code the input code snippet to be processed.
* @param currentcodeindex the current index in the code snippet for processing.
* @param codelen the length of the code snippet.
* @param tokens pointer to the tokenlist structure where tokens will be stored.
*
* @return the number of characters consumed to tokenize the keyword, or -1 if no keyword is found.
*/
int tokenizeKeywords(const char* code, int currentCodeIndex, int codeLen, struct List* tokens) {

    if (isKeyword("THEN", 4, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = THEN,
                        .lexeme = ""
                }
        });
        return 4;
    }

    if (isKeyword("IF", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = IF,
                        .lexeme = ""
                }
        });
        return 2;
    }

    if (isKeyword("MOD", 3, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = MODULO,
                        .lexeme = ""
                }
        });
        return 3;
    }

    if (isKeyword("<>", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = NOT_EQUALS,
                        .lexeme = ""
                }
        });
        return 2;
    }

    if (isKeyword("ENDIF", 5, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = ENDIF,
                        .lexeme = ""
                }
        });
        return 5;
    }

    if (isKeyword("ELSE", 4, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = ELSE,
                        .lexeme = ""
                }
        });
        return 4;
    }

    if (isKeyword("TRUE", 4, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = BOOLEAN,
                        .lexeme = "TRUE"
                }
        });
        return 4;
    }

    if (isKeyword("FALSE", 5, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = BOOLEAN,
                        .lexeme = "FALSE"
                }
        });
        return 5;
    }

    if (isKeyword("BOOLEAN", 7, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = BOOLEAN_IDENTIFIER,
                        .lexeme = ""
                }
        });
        return 7;
    }

    if (isKeyword("OUTPUT", 6, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = OUTPUT,
                        .lexeme = ""
                }
        });
        return 6;
    }

    if (isKeyword("DECLARE", 7, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = DECLARE,
                        .lexeme = ""
                }
        });
        return 7;
    }

    if (isKeyword("INTEGER", 7, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = INTEGER_IDENTIFIER,
                        .lexeme = ""
                }
        });
        return 7;
    }

    if (isKeyword("REAL", 4, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = REAL_IDENTIFIER,
                        .lexeme = ""
                }
        });
        return 4;
    }

    if (isKeyword("<-", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = ASSIGNMENT,
                        .lexeme = ""
                }
        });
        return 2;
    }

    if (isKeyword("<=", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = LESSER_OR_EQUALS,
                        .lexeme = ""
                }
        });
        return 2;
    }

    if (isKeyword(">=", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = GREATER_OR_EQUALS,
                        .lexeme = ""
                }
        });
        return 2;
    }

    if (isKeyword("OR", 2, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = OR,
                        .lexeme = ""
                }
        });
        return 2;
    }

    if (isKeyword("AND", 3, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = AND,
                        .lexeme = ""
                }
        });
        return 3;
    }

    if (isKeyword("NOT", 3, code, currentCodeIndex, codeLen)) {
        listAppend(tokens, (union listValue) {
                .tokenValue = {
                        .type = NOT,
                        .lexeme = ""
                }
        });
        return 3;
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
            .tokenValue = {
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
    if (!isalpha(code[currentCodeIndex])) {
        return -1;
    }

    int i = currentCodeIndex + 1;

    while (i < codeLen && (isalpha(code[i]) || isdigit(code[i]) || code[i] == '_')) {
        i++;
    }

    int lexemeLen = i - currentCodeIndex;
    char* lexeme = (char*)malloc(lexemeLen + 1);
    strncpy(lexeme, code + currentCodeIndex, lexemeLen);
    lexeme[lexemeLen] = '\0';

    // Create a union listValue with a struct Token and set its values
    union listValue tokenValue;
    tokenValue.tokenValue.type = IDENTIFIER;
    tokenValue.tokenValue.lexeme = lexeme;

    // Append the tokenValue to the list
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
        int keywordLen = tokenizeKeywords(code, i, codeLen, tokens);
        if (keywordLen != -1) {
            i += keywordLen - 1;
            continue;
        }

        if (tokenizeOneChar(code[i], tokens)) {
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

/**
 * Print the content of a Token structure including the Type and Lexeme.
 *
 * @param token the tokenValue to be printed.
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
        printf("index: %d\n", i);
        printToken(tokens->array[i].tokenValue);
    }
};