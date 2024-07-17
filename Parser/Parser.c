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
        returnValue->isConstant = 1;
        return returnValue;
    }

    int i = startIndex;
    int bestOperationIndex = -1;
    int is_not = 0;
    int operationLevel = 0;

    while (i <= endIndex){
        if (tokens->array[i].tokenValue.type == OPEN_PAREN){
            i = findClosingParen(i, tokens, endIndex) + 1;
            continue;
        }

        switch (tokens->array[i].tokenValue.type) {

            case AND:
            case OR:
                if (operationLevel < 4){
                    bestOperationIndex = i;
                    operationLevel = 4;
                }
                break;

            case NOT:
                if (operationLevel < 5){
                    bestOperationIndex = i;
                    operationLevel = 5;
                    is_not = 1;
                }
                break;

            case EQUALS:
            case NOT_EQUALS:
            case GREATER:
            case LESSER:
            case GREATER_OR_EQUALS:
            case LESSER_OR_EQUALS:
                if (operationLevel < 3){
                    bestOperationIndex = i;
                    operationLevel = 3;
                }
                break;

            case ADDITION:
            case SUBTRACTION:
                if (operationLevel < 2){
                    bestOperationIndex = i;
                    operationLevel = 2;
                }
                break;

            case DIVISION:
            case MULTIPLICATION:
            case MODULO:
                if (operationLevel < 1){
                    bestOperationIndex = i;
                    operationLevel = 1;
                }
                break;
        };
        i++;
    };

    struct Expression* returnValue = (struct Expression*)malloc(sizeof(struct Expression));

    returnValue->left = NULL;
    if (!is_not) {
        returnValue->left = parseExpression(tokens, startIndex, bestOperationIndex - 1);
    }


    returnValue->right = parseExpression(tokens, bestOperationIndex+1, endIndex);
    returnValue->type = tokens->array[bestOperationIndex].tokenValue.type;
    returnValue->isConstant = 0;
    return returnValue;
};

/**
* Parses a list of tokens into an abstract syntax tree (AST).
*
* @param tokens The list of tokens.
*
* @return The AST as a list of ASTNodes.
*/
int parse(struct List* tokens, struct List* ASTList, enum ParserStatus status, int startIndex){
    int lineStartIndex, newlineIndex = startIndex-1;
    int moveStartIndex = 0, newStartIndex = 0;
    struct ASTNode newNode;

    while (newlineIndex < tokens->head) {
        newlineIndex++;
        lineStartIndex = newlineIndex;
        if (moveStartIndex){
            lineStartIndex = newStartIndex;
            newlineIndex = newStartIndex;
            moveStartIndex = 0;
        }
        while (newlineIndex < tokens->head && tokens->array[newlineIndex].tokenValue.type != NEW_LINE)
            newlineIndex++;
        if (lineStartIndex == newlineIndex)
            break;
        
        if (status == P_IF || status == P_ELSE){
            if (tokens->array[lineStartIndex].tokenValue.type == ENDIF ||
                tokens->array[lineStartIndex].tokenValue.type == ELSE){
                return newlineIndex - startIndex - 1;
                }
        }
        if (tokens->array[lineStartIndex].tokenValue.type == IF){
            moveStartIndex = 1;
            newStartIndex = parseIf(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == ELSE){
            moveStartIndex = 1;
            newStartIndex = parseElse(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == DECLARE)
            parseDeclare(&newNode, tokens, lineStartIndex);
        else if (tokens->array[lineStartIndex + 1].tokenValue.type == ASSIGNMENT)
            parseAssignment(&newNode, tokens, lineStartIndex, newlineIndex);
        else if (tokens->array[lineStartIndex].tokenValue.type == OUTPUT)
            parseOutput(&newNode, tokens, lineStartIndex, newlineIndex);

        listAppend(ASTList, (union listValue)newNode);
    }
    return newlineIndex - startIndex;
};


    // struct List* ASTList = listInit(ASTNode);
    // // Two indexes that form an inclusive range representing the currant line of code.
    // int end = start;
    // int linesToSkip = -1;
    // int linesSkipped = 0;

    // while (end < tokens->head){
    //     while (end+1 < tokens->head && tokens->array[end+1].tokenValue.type != NEW_LINE){
    //         end++;
    //     }

    //      if (linesToSkip != -1 && linesSkipped < linesToSkip){
    //         linesSkipped++;
    //         end += 2;
    //         start = end;
    //         continue;
    //     }

    //     if (linesToSkip != -1){
    //         linesToSkip = -1;
    //         linesSkipped = 0;
    //     }

    //     if (start == end){
    //         if (haltToken != NULL_TYPE && haltToken == tokens->array[start].tokenValue.type){
    //             break;
    //         }
    //         end += 2;
    //         continue;
    //     }

    //     struct ASTNode newNode;
    //     if (tokens->array[start].tokenValue.type == DECLARE) {
    //         newNode.type = DECLARE;
    //         newNode.value.declare = (struct ASTDeclare){.type=tokens->array[start+3].tokenValue.type,
    //                                                     .identifier=tokens->array[start+1].tokenValue.lexeme};
    //     }
    //     else if (tokens->array[start+1].tokenValue.type == ASSIGNMENT) {
    //         newNode.type = ASSIGNMENT;
    //         newNode.value.assignment = (struct ASTAssignment){.identifier = tokens->array[start].tokenValue.lexeme,
    //                                                             .value = parseExpression(tokens, start+2, end)};
    //     }
    //     else if (tokens->array[start].tokenValue.type == OUTPUT) {
    //         newNode.type = OUTPUT;
    //         newNode.value.output = (struct ASTOutput){.value = parseExpression(tokens, start+1, end)};
    //     }

    //     else if (tokens->array[start].tokenValue.type == IF){
    //         struct List* content = parse(tokens, end+2, ENDIF);
    //         newNode.type = IF;
    //         newNode.value.If = (struct ASTif){.test=parseExpression(tokens, start+1, end-1),
    //                                             .content=content};
    //         linesToSkip = content->head+1;
    //     }
    //     listAppend(ASTList, (union listValue)newNode);

    //     end += 2; // Skipping over the previous NEW_LINE.
    //     start = end;

    // }
    // return ASTList;

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
            case OUTPUT:
                printf("OUTPUT: {value: ");
                printExpression(AST->array[i].astNodeValue.value.output.value);
                printf("}\n");
                continue;
            case IF:
                printf("IF: {test: ");
                printExpression(AST->array[i].astNodeValue.value.If.test);
                printf(", code: ");
                printASTList(AST->array[i].astNodeValue.value.If.content);
                printf("}\n");
                continue;
            case ELSE:
                printf("ELSE: {code: ");
                printASTList(AST->array[i].astNodeValue.value.Else.content);
                printf("}\n");
        }
    }
}

/**
* Prints the given expression.
*
* @param expression The expression to print.
*/
void printExpression(struct Expression* expression){
    if (expression->isConstant) {
        printf(" %s ", expression->lexeme);
        return;
    }

    printf("(");
    if (expression->type == NOT){
        printf("NOT ");
        printExpression(expression->right);
        printf(")");
        return;
    }

    printExpression(expression->right);
    printf("%s", tokenTypeToString(expression->type));
    printExpression(expression->left);
    printf(")");
};