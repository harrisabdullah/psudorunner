//
// Created by Harris on 05/01/2024.
//

#include "../common/List.h"
#include "../common/tokenTypeToString.h"
#include "../errors/internalErrors.h"
#include "../errors/errors.h"
#include "../errors/syntaxChecker.h"
#include "Parser.h"
#include "ASTNode.h"
#include <stdio.h>
#include <stdlib.h>


int findClosingParen(int openParenIndex, List tokens, int endIndex, enum TokenType open, enum TokenType close){
    int depth = 1;
    for (int i=openParenIndex+1; i<=endIndex; i++) {
        if (((Token*)tokens.items[i])->type == open) {
            depth++;
        } else if (((Token*)tokens.items[i])->type == close) {
            depth--;

            if (depth == 0) {
                return i;
            }
        }
    }
    return 0;
}

int isTypeIdentifier(Token* t){
    return t->type == INTEGER_IDENTIFIER ||
           t->type == REAL_IDENTIFIER ||
           t->type == BOOLEAN_IDENTIFIER ||
           t->type == STRING_IDENTIFIER;
}

struct Expression* parseExpression(List tokens, int startIndex, int endIndex, char* code){
    if (((Token*)tokens.items[startIndex])->type == OPEN_PAREN &&
        ((Token*)tokens.items[endIndex])->type == CLOSE_PAREN) {
        startIndex++;
        endIndex--;
    }

    struct Expression* returnValue = (struct Expression*)malloc(sizeof(struct Expression));
    if (startIndex == endIndex){
        if (((Token*)tokens.items[startIndex])->type == IDENTIFIER){
            struct Identifier identifier_s;
            identifier_s.lexeme = ((Token*)tokens.items[startIndex])->lexeme;
            identifier_s.hasIndex = 0;

            returnValue->type = IDENTIFIER;
            returnValue->isConstant = 1;
            returnValue->identifier = identifier_s;
            return returnValue;
        }
        
        syn_checkConst(startIndex, tokens, code);
        returnValue->type = ((Token*)tokens.items[startIndex])->type;
        returnValue->lexeme = ((Token*)tokens.items[startIndex])->lexeme;
        returnValue->isConstant = 1;
        return returnValue;
    }

    // function calls
    if ((((Token*)tokens.items[startIndex])->type == IDENTIFIER ||
    isTypeIdentifier((Token*)tokens.items[startIndex])) &&
    ((Token*)tokens.items[startIndex+1])->type == OPEN_PAREN &&
    ((Token*)tokens.items[endIndex])->type == CLOSE_PAREN){
        returnValue->type = FUNCTION_CALL;
        returnValue->isConstant = 1;
        returnValue->funcCall = parseFuncCall(tokens, startIndex, endIndex, code);
        return returnValue;
    }

    // indexing
    if (((Token*)tokens.items[startIndex])->type == IDENTIFIER &&
    ((Token*)tokens.items[startIndex+1])->type == OPEN_SQUARE_PAREN &&
    ((Token*)tokens.items[endIndex])->type == CLOSE_SQUARE_PAREN) {
        struct Identifier identifier_s;
        identifier_s.lexeme = ((Token*)tokens.items[startIndex])->lexeme;
        identifier_s.hasIndex = 1;
        identifier_s.indexExpression = parseExpression(tokens, startIndex+2, endIndex-1, code);

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
        if (((Token*)tokens.items[i])->type == OPEN_PAREN){
            i = findClosingParen(i, tokens, endIndex, OPEN_PAREN, CLOSE_PAREN) + 1;
            continue;
        }

        if (((Token*)tokens.items[i])->type == OPEN_SQUARE_PAREN){
            i = findClosingParen(i, tokens, endIndex, OPEN_SQUARE_PAREN, CLOSE_SQUARE_PAREN) + 1;
            continue;
        }

        switch (((Token*)tokens.items[i])->type) {

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
        returnValue->left = parseExpression(tokens, startIndex, bestOperationIndex - 1, code);
    }


    returnValue->right = parseExpression(tokens, bestOperationIndex+1, endIndex, code);
    returnValue->type = ((Token*)tokens.items[bestOperationIndex])->type;
    returnValue->isConstant = 0;
    return returnValue;
};


int parse(List* ASTList, List tokens, enum ParserStatus status, int startIndex, char* code){
    enum TokenType currantType;
    int lineStartIndex, newlineIndex = startIndex-1;
    int moveStartIndex = 0, newStartIndex = 0;
     ASTNode* newNode;
    while (newlineIndex < tokens.length) {
        newlineIndex++;
        lineStartIndex = newlineIndex;
        if (moveStartIndex){
            if (newStartIndex >= tokens.length){
                break;
            }
            lineStartIndex = newStartIndex;
            newlineIndex = newStartIndex;
            moveStartIndex = 0;
        }
        while (newlineIndex < tokens.length && ((Token*)tokens.items[newlineIndex])->type != NEW_LINE){
            newlineIndex++;
        }
        if (lineStartIndex == newlineIndex){
            continue;
        }
        currantType = ((Token*)tokens.items[lineStartIndex])->type;
        if (status == P_IF || status == P_ELSE){
            if (currantType == ENDIF ||
                currantType == ELSE){
                break;
                }
        }
        if (status == P_WHILE){
            if (currantType == ENDWHILE){
                break;
            }
        }
        if (status == P_REPEAT){
            if (currantType == UNTIL){
                break;
            }
        }
        if (status == P_FOR){
            if (currantType == NEXT){
                break;
            }
        }

        newNode = malloc(sizeof(ASTNode));
        if (newNode == NULL){
            ie_allocationError();
        }
        if (currantType == IF){
            moveStartIndex = 1;
            newStartIndex = parseIf(newNode, tokens, lineStartIndex, newlineIndex, code) + newlineIndex + 3;
        }
        else if (currantType == ELSE){
            moveStartIndex = 1;
            newStartIndex = parseElse(newNode, tokens, lineStartIndex, newlineIndex, code) + newlineIndex + 3;
        }
        else if (currantType == WHILE){
            moveStartIndex = 1;
            newStartIndex = parseWhile(newNode, tokens, lineStartIndex, newlineIndex, code) + newlineIndex + 3;
        }
        else if (currantType == REPEAT){
            moveStartIndex = 1;
            newStartIndex = parseRepeat(newNode, tokens, lineStartIndex, newlineIndex, code) + newlineIndex + 3;
        }
        else if (currantType == FOR){
            moveStartIndex = 1;
            newStartIndex = parseFor(newNode, tokens, lineStartIndex, newlineIndex, code) + newlineIndex + 3;
        }
        else if (currantType == DECLARE){
            parseDeclare(newNode, tokens, lineStartIndex);
        }
        else if (currantType == IDENTIFIER){
            parseAssignment(newNode, tokens, lineStartIndex, newlineIndex, code);
        }
        else if (currantType == OUTPUT){
            parseOutput(newNode, tokens, lineStartIndex, newlineIndex, code);
        }
        listAppend(ASTList, newNode);
    }
    return newlineIndex - startIndex - 1;
};


void printASTList(List AST){
    for (int i=0; i<AST.length; i++){
        switch (((ASTNode*)AST.items[i])->type) {
            case DECLARE:
                printf("DECLARE: {identifier: %s, type: %s}\n", ((ASTNode*)AST.items[i])->value.declare.identifier,
                       tokenTypeToString(((ASTNode*)AST.items[i])->value.declare.type));
                continue;
            case ASSIGNMENT:
                printf("ASSIGMENT: {identifier: %s, expression: ", ((ASTNode*)AST.items[i])->value.assignment.identifier.lexeme);
                printExpression(((ASTNode*)AST.items[i])->value.assignment.value);
                if (((ASTNode*)AST.items[i])->value.assignment.identifier.hasIndex){
                    printf(", index: ");
                    printExpression(((ASTNode*)AST.items[i])->value.assignment.identifier.indexExpression);
                }
                printf("}\n");
                continue;
            case OUTPUT:
                printf("OUTPUT: {value: ");
                printExpression(((ASTNode*)AST.items[i])->value.output.value);
                printf("}\n");
                continue;
            case IF:
                printf("IF: {test: ");
                printExpression(((ASTNode*)AST.items[i])->value.If.test);
                printf(", code: ");
                printASTList(*(((ASTNode*)AST.items[i])->value.If.content));
                printf("}\n");
                continue;
            case ELSE:
                printf("ELSE: {code: ");
                printASTList(*(((ASTNode*)AST.items[i])->value.Else.content));
                printf("}\n");

            case WHILE:
                printf("WHILE: {condition: ");
                printExpression(((ASTNode*)AST.items[i])->value.While.condition);
                printf(", code: ");
                printASTList(*(((ASTNode*)AST.items[i])->value.While.content));
                printf("}\n");
            case REPEAT:
                printf("REPEAT UNTIL: {condition: ");
                printExpression(((ASTNode*)AST.items[i])->value.Repeat.condition);
                printf(", code: ");
                printASTList(*(((ASTNode*)AST.items[i])->value.Repeat.content));
                printf("}\n");
            case FOR:
                printf("FOR: {range: ");
                printExpression(((ASTNode*)AST.items[i])->value.For.rangeMin);
                printf(" -> ");
                printExpression(((ASTNode*)AST.items[i])->value.For.rangeMax);
                printf(", code: ");
                printASTList(*(((ASTNode*)AST.items[i])->value.For.content));
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

        if (expression->type == FUNCTION_CALL){
            printf(" %s(", expression->funcCall.lexeme);
            for (int i=0; i<expression->funcCall.args.length; i++){
                printExpression(expression->funcCall.args.items[i]);
                printf(", ");
            }
            printf(") ");
            return;
        }

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