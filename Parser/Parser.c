//
// Created by Harris on 05/01/2024.
//

#include "../common/List.h"
#include "../common/tokenTypeToString.h"
#include "Parser.h"
#include "ASTNode.h"
#include <stdio.h>
#include <stdlib.h>

/**
* Finds the index of the closing parenthesis that corresponds to the given opening parenthesis index.
*
* @param openParenIndex The index of the opening parenthesis.
* @param tokens The list of tokens.
* @param endIndex The index of the last token to consider.
*
* @return The index of the closing parenthesis, or 0 if not found.
*/
int findClosingParen(int openParenIndex, struct List* tokens, int endIndex){
    int depth = 1;
    for (int i=openParenIndex+1; i<=endIndex; i++) {
        if (tokens->array[i].tokenValue.type == OPEN_PAREN) {
            depth++;
        } else if (tokens->array[i].tokenValue.type == CLOSE_PAREN) {
            depth--;

            if (depth == 0) {
                return i;
            }
        }
    }
    return 0;
}

/**
* Parses an expression from a list of tokens.
*
* @param tokens The list of tokens.
* @param startIndex The index of the first token in the expression.
* @param endIndex The index of the last token in the expression.
*
* @return A pointer to the parsed expression.
*/
struct Expression* parseExpression(struct List* tokens, int startIndex, int endIndex) {
    if (tokens->array[startIndex].tokenValue.type == OPEN_PAREN &&
        tokens->array[endIndex].tokenValue.type == CLOSE_PAREN) {
        startIndex++;
        endIndex--;
    }

    if (startIndex == endIndex){
        struct Expression* returnValue = (struct Expression*)malloc(sizeof(struct Expression));
        returnValue->type = tokens->array[startIndex].tokenValue.type;
        returnValue->lexeme = tokens->array[startIndex].tokenValue.lexeme;
        return returnValue;
    }

    int i = startIndex;
    int bestOperationIndex = -1;
    int operationLevel = 0; // the importance of the operation, 0 means NULL,
    // 1 means addition or subtraction
    // and 2 means division or multiplication
    while (i <= endIndex){
        if (tokens->array[i].tokenValue.type == OPEN_PAREN){
            i = findClosingParen(i, tokens, endIndex) + 1;
            continue;
        }

        switch (tokens->array[i].tokenValue.type) {

            case ADDITION:
            case SUBTRACTION:
                if (operationLevel < 2){
                    bestOperationIndex = i;
                    operationLevel = 2;
                }

            case DIVISION:
            case MULTIPLICATION:
                if (operationLevel < 1){
                    bestOperationIndex = i;
                    operationLevel = 1;
                }

            default:
                i++;
        };
    };


    struct Expression* returnValue = (struct Expression*)malloc(sizeof(struct Expression));
    returnValue->left = parseExpression(tokens, startIndex, bestOperationIndex-1);
    returnValue->right = parseExpression(tokens, bestOperationIndex+1, endIndex);
    returnValue->type = tokens->array[bestOperationIndex].tokenValue.type;
    return returnValue;
};

/**
* Parses a list of tokens into an abstract syntax tree (AST).
*
* @param tokens The list of tokens.
*
* @return The AST as a list of ASTNodes.
*/
struct List* parse(struct List* tokens){
    struct List* ASTList = listInit(ASTNode);
    // Two indexes that form an inclusive range representing the currant line of code.
    int start = 0;
    int end = 0;

    while (end < tokens->head){
        while (end+1 < tokens->head && tokens->array[end+1].tokenValue.type != NEW_LINE){
            end++;
        }
        // If this line is empty. i.e. two new lines next to each other or a newline then EOF.
        if (start == end){
            continue;
        }

        struct ASTNode newNode;
        if (tokens->array[start].tokenValue.type == DECLARE) {
            newNode.type = DECLARE;
            newNode.value.declare = (struct ASTDeclare){.type=tokens->array[start+3].tokenValue.type,
                                                        .identifier=tokens->array[start+1].tokenValue.lexeme};
        }
        else if (tokens->array[start+1].tokenValue.type == ASSIGNMENT) {
            newNode.type = ASSIGNMENT;
            newNode.value.assignment = (struct ASTAssignment){.identifier = tokens->array[start].tokenValue.lexeme,
                                                                .value = parseExpression(tokens, start+2, end)};
        }

        listAppend(ASTList, (union listValue)newNode);

        // Moving to the next line of code.
        end += 2; // Skipping over the previous NEW_LINE.
        start = end;

    }
    return ASTList;
};

/**
* Prints the given AST list.
*
* @param AST The AST list to print.
*/
void printASTList(struct List* AST){
    for (int i=0; i<AST->head; i++){
        switch (AST->array[i].astNodeValue.type) {
            case DECLARE:
                printf("DECLARE: {identifier: %s, type: %s}\n", AST->array[i].astNodeValue.value.declare.identifier,
                       tokenTypeToString(AST->array->astNodeValue.value.declare.type));
                continue;
            case ASSIGNMENT:
                printf("ASSIGMENT: {identifier: %s, expression: ", AST->array[i].astNodeValue.value.assignment.identifier);
                printExpression(AST->array[i].astNodeValue.value.assignment.value);
                printf("}\n");
                continue;
        }
    }
}

/**
* Prints the given expression.
*
* @param expression The expression to print.
*/
void printExpression(struct Expression* expression){
    if (expression->type == INTEGER || expression->type == REAL || expression->type == IDENTIFIER) {
        printf("%s", expression->lexeme);
        return;
    }

    printf("(");
    printExpression(expression->right);

    switch (expression->type) {
        case ADDITION:
            printf("+");
            break;
        case SUBTRACTION:
            printf("-");
            break;
        case DIVISION:
            printf("/");
            break;
        case MULTIPLICATION:
            printf("*");
            break;
        default:
            // Handle unknown expression type
            break;
    }

    printExpression(expression->left);
    printf(")");
};