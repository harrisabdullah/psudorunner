//
// Created by Harris on 05/01/2024.
//

#include "../common/List.h"
#include "Parser.h"
#include "ASTNode.h"
#include <stdio.h>
#include <stdlib.h>

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

struct Expression* parseExpression(struct List* tokens, int startIndex, int endIndex) {
    if (tokens->array[startIndex].tokenValue.type == OPEN_PAREN &&
        tokens->array[endIndex].tokenValue.type == CLOSE_PAREN) {
        startIndex++;
        endIndex++;
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
            case DIVISION:
            case MULTIPLICATION:
                if (operationLevel < 2){
                    bestOperationIndex = i;
                    operationLevel = 2;
                }
                continue;

            case ADDITION:
            case SUBTRACTION:
                if (operationLevel < 1){
                    bestOperationIndex = i;
                    operationLevel = 1;
                }
                continue;

            default:
                continue;
        };
        i++;
    };


    struct Expression* returnValue = (struct Expression*)malloc(sizeof(struct Expression));
    returnValue->left = parseExpression(tokens, startIndex, bestOperationIndex-1);
    returnValue->right = parseExpression(tokens, bestOperationIndex+1, endIndex);
    returnValue->type = tokens->array[bestOperationIndex].tokenValue.type;
    return returnValue;
};

struct List* parse(struct List* tokens){
    struct List* ASTList = listInit(ASTNode);
    // Two indexes that form an inclusive range representing the currant line of code.
    int start = 0;
    int end = 0;

    while (end < tokens->head){
        // Moving to the next line of code.
        end += 2; // Skipping over the previous NEW_LINE.
        start = end;

        while (end < tokens->head && tokens->array[end].tokenValue.type != NEW_LINE){
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
    }
};