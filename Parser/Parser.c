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
int findClosingParen(int openParenIndex, struct List* tokens, int endIndex, enum TokenType open, enum TokenType close){
    int depth = 1;
    for (int i=openParenIndex+1; i<=endIndex; i++) {
        if (tokens->array[i].tokenValue.type == open) {
            depth++;
        } else if (tokens->array[i].tokenValue.type == close) {
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

    struct Expression* returnValue = (struct Expression*)malloc(sizeof(struct Expression));
    if (startIndex == endIndex){
        if (tokens->array[startIndex].tokenValue.type == IDENTIFIER){
            struct Identifier identifier_s;
            identifier_s.lexeme = tokens->array[startIndex].tokenValue.lexeme;
            identifier_s.hasIndex = 0;

            returnValue->type = IDENTIFIER;
            returnValue->isConstant = 1;
            returnValue->identifier = identifier_s;
            return returnValue;
        }
        
        returnValue->type = tokens->array[startIndex].tokenValue.type;
        returnValue->lexeme = tokens->array[startIndex].tokenValue.lexeme;
        returnValue->isConstant = 1;
        return returnValue;
    }

    if (tokens->array[startIndex].tokenValue.type == IDENTIFIER &&
    tokens->array[startIndex+1].tokenValue.type == OPEN_SQUARE_PAREN &&
    tokens->array[endIndex].tokenValue.type == CLOSE_SQUARE_PAREN) {
        struct Identifier identifier_s;
        identifier_s.lexeme = tokens->array[startIndex].tokenValue.lexeme;
        identifier_s.hasIndex = 1;
        identifier_s.indexExpression = parseExpression(tokens, startIndex+2, endIndex-1);

        returnValue->type = IDENTIFIER;
        returnValue->isConstant = 1;
        returnValue->identifier = identifier_s;
        return returnValue;
    }

    int i = startIndex;
    int bestOperationIndex = -1;
    int is_not = 0;
    int operationLevel = 0;

    while (i <= endIndex){
        if (tokens->array[i].tokenValue.type == OPEN_PAREN){
            i = findClosingParen(i, tokens, endIndex, OPEN_PAREN, CLOSE_PAREN) + 1;
            continue;
        }

        if (tokens->array[i].tokenValue.type == OPEN_SQUARE_PAREN){
            i = findClosingParen(i, tokens, endIndex, OPEN_SQUARE_PAREN, CLOSE_SQUARE_PAREN) + 1;
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
            if (newStartIndex >= tokens->head){
                break;
            }
            lineStartIndex = newStartIndex;
            newlineIndex = newStartIndex;
            moveStartIndex = 0;
        }
        while (newlineIndex < tokens->head && tokens->array[newlineIndex].tokenValue.type != NEW_LINE){
            newlineIndex++;
        }
        if (lineStartIndex == newlineIndex){
            break;
        }
        if (status == P_IF || status == P_ELSE){
            if (tokens->array[lineStartIndex].tokenValue.type == ENDIF ||
                tokens->array[lineStartIndex].tokenValue.type == ELSE){
                break;
                }
        }
        if (status == P_WHILE){
            if (tokens->array[lineStartIndex].tokenValue.type == ENDWHILE){
                break;
            }
        }
        if (status == P_REPEAT){
            if (tokens->array[lineStartIndex].tokenValue.type == UNTIL){
                break;
            }
        }
        if (status == P_FOR){
            if (tokens->array[lineStartIndex].tokenValue.type == NEXT){
                break;
            }
        }

        if (tokens->array[lineStartIndex].tokenValue.type == IF){
            moveStartIndex = 1;
            newStartIndex = parseIf(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex + 3;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == ELSE){
            moveStartIndex = 1;
            newStartIndex = parseElse(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex + 3;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == WHILE){
            moveStartIndex = 1;
            newStartIndex = parseWhile(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex + 3;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == REPEAT){
            moveStartIndex = 1;
            newStartIndex = parseRepeat(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex + 3;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == FOR){
            moveStartIndex = 1;
            newStartIndex = parseFor(&newNode, tokens, lineStartIndex, newlineIndex) + newlineIndex + 3;
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == DECLARE){
            parseDeclare(&newNode, tokens, lineStartIndex);
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == IDENTIFIER){
            parseAssignment(&newNode, tokens, lineStartIndex, newlineIndex);
        }
        else if (tokens->array[lineStartIndex].tokenValue.type == OUTPUT){
            parseOutput(&newNode, tokens, lineStartIndex, newlineIndex);
        }
        listAppend(ASTList, (union listValue)newNode);
    }
    return newlineIndex - startIndex - 1;
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
                printf("ASSIGMENT: {identifier: %s, expression: ", AST->array[i].astNodeValue.value.assignment.identifier.lexeme);
                printExpression(AST->array[i].astNodeValue.value.assignment.value);
                if (AST->array[i].astNodeValue.value.assignment.identifier.hasIndex){
                    printf(", index: ");
                    printExpression(AST->array[i].astNodeValue.value.assignment.identifier.indexExpression);
                }
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

            case WHILE:
                printf("WHILE: {condition: ");
                printExpression(AST->array[i].astNodeValue.value.While.condition);
                printf(", code: ");
                printASTList(AST->array[i].astNodeValue.value.While.content);
                printf("}\n");
            case REPEAT:
                printf("REPEAT UNTIL: {condition: ");
                printExpression(AST->array[i].astNodeValue.value.Repeat.condition);
                printf(", code: ");
                printASTList(AST->array[i].astNodeValue.value.Repeat.content);
                printf("}\n");
            case FOR:
                printf("FOR: {range: ");
                printExpression(AST->array[i].astNodeValue.value.For.rangeMin);
                printf(" -> ");
                printExpression(AST->array[i].astNodeValue.value.For.rangeMax);
                printf(", code: ");
                printASTList(AST->array[i].astNodeValue.value.For.content);
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
        if (expression->type == IDENTIFIER){
            if (expression->identifier.hasIndex){
                printf(" %s[", expression->identifier.lexeme);
                printExpression(expression->identifier.indexExpression);
                printf("] ");
            } else {
                printf(" %s ", expression->identifier.lexeme);
            }
            return;
        };

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