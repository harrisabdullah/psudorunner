//
// Created by Harris on 09/04/2024.
//

#include "Resolver.h"
#include "../common/List.h"
#include "../common/Stack.h"
#include "../common/tokenTypeToString.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Converts a string representation of a variable value to a VariableValue struct.
 *
 * @param type: The type of the variable value.
 * @param data: The string representation of the variable value.
 * @param namespace: The namespace list to search for identifiers.
 *
 * @return: A pointer to the VariableValue struct.
 */
struct VariableValue* stringToVariableValue(enum TokenType type, char* data, struct List* namespace){
    if (type == IDENTIFIER){
        for (int i=0; i<namespace->head; i++){
            if (strcmp(data, namespace->array[i].variable.variableName) == 0){
                return &namespace->array[i].variable.value;
            }
        }
    }
    struct VariableValue* result = (struct VariableValue*)malloc(sizeof(struct VariableValue));
    if (result == NULL) {
        perror("Variable allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    result->type = type;

    switch(type) {
        case REAL:
            result->data.real = atof(data);
            break;
        case INTEGER:
            result->data.integer = atoi(data);
            break;
        case BOOLEAN:
            result->data.boolean = strcmp(data, "TRUE") == 0;
    }

    return result;
}

/**
 * Resolves an expression to a variable value.
 *
 * @param namespace: The namespace list to search for variable values.
 * @param expression: The expression to resolve.
 *
 * @return: A pointer to the resolved VariableValue struct.
 */

 // you dont need to return anything 
void resolveExpression(struct List* namespace, struct Expression* expression, struct Stack* stack){
    if (expression->isConstant){
        stackPush(stack, stringToVariableValue(expression->type, expression->lexeme, namespace));
        return;
    }

    struct VariableValue* result = (struct VariableValue*)calloc(1, sizeof(struct VariableValue));

    if (result == NULL){
        perror("allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (expression->type == NOT){
        resolveExpression(namespace, expression->right, stack);
        if (stackTypePeek(stack, 0) != BOOLEAN){
            printf("typeerror: NOT\n");
            exit(EXIT_FAILURE);
            // TODO: type error
        }
        result->type = BOOLEAN;
        result->data.boolean = !stackPop(stack)->data.boolean;
        stackPush(stack, result);
        return;
    }

    resolveExpression(namespace, expression->right, stack);
    resolveExpression(namespace, expression->left, stack);
    enum TokenType leftType = stackTypePeek(stack, 0);
    enum TokenType rightType = stackTypePeek(stack, 1);

    // boolean operations 
    if (expression->type == AND || expression->type == OR){
        if (leftType != BOOLEAN || rightType != BOOLEAN){
            // todo: type error
            printf("typeerror: AND OR\n");
            exit(EXIT_FAILURE);
        }

        result->type = BOOLEAN;

        if (expression->type == AND){
            result->data.boolean = stackPop(stack)->data.boolean && stackPop(stack)->data.boolean; 
        } else if (expression->type == OR) {
            // Makes sure both values get popped.
            // If it was inline then when the first value resovles to 1 it doesnt bother computing the second.
            // I spent days finding this stupid bug.
            int leftValue = stackPop(stack)->data.boolean;
            int rightValue = stackPop(stack)->data.boolean;

            result->data.boolean = leftValue || rightValue;
            result->data.boolean = 1;
        }
        stackPush(stack, result);
        return;
    }

    if ((leftType != INTEGER && leftType != REAL) || (rightType != INTEGER && rightType != REAL)){
            // todo: type error
            printf("typeerror");
        }

    if (expression->type == DIVISION){
        float leftValue;
        float rightValue;

        if (leftType == INTEGER){
            leftValue = (float)stackPop(stack)->data.integer;
        } else {
            leftValue = stackPop(stack)->data.real;
        }
        if (rightType == INTEGER){
            rightValue = (float)stackPop(stack)->data.integer;
        } else {
            rightValue = stackPop(stack)->data.real;
        }

        result->type = REAL;
        result->data.real = leftValue / rightValue;
        stackPush(stack, result);
        return;
    }

    if (expression->type == EQUALS){
        result->type = BOOLEAN;
        if (leftType == BOOLEAN && rightType == BOOLEAN){
            result->data.boolean = stackPop(stack)->data.boolean == stackPop(stack)->data.boolean;
            stackPush(stack, result);
            return;
        }

        float leftValue;
        float rightValue;

        if (leftType == INTEGER){
            leftValue = (float)stackPop(stack)->data.integer;
        } else {
            leftValue = stackPop(stack)->data.real;
        }
        if (rightType == INTEGER){
            rightValue = (float)stackPop(stack)->data.integer;
        } else {
            rightValue = stackPop(stack)->data.real;
        }
        result->data.boolean = leftValue == rightValue;
        stackPush(stack, result);
        return;
    }

    float realLeftValue;
    float realRightValue; 

    if (leftType == INTEGER && rightType == INTEGER){
        result->type = INTEGER;
    } else {
        result->type = REAL;
        
        if (leftType == INTEGER){
            realLeftValue = (float)stackPop(stack)->data.integer;
        } else {
            realLeftValue = stackPop(stack)->data.real;
        }

        if (rightType == INTEGER){
            realRightValue = (float)stackPop(stack)->data.integer;
        } else {
            realRightValue = stackPop(stack)->data.real;
        }
    }

    if (expression->type == ADDITION){
        if (result->type == INTEGER){
            result->data.integer = stackPop(stack)->data.integer + stackPop(stack)->data.integer;
        } else {
            result->data.real = realLeftValue + realRightValue;
        }
    }
    else if (expression->type == SUBTRACTION){
        if (result->type == INTEGER){
            result->data.integer = stackPop(stack)->data.integer - stackPop(stack)->data.integer;
        } else {
            result->data.real = realLeftValue - realRightValue;
        }
    }
    else if (expression->type == MULTIPLICATION){
        if (result->type == INTEGER){
            result->data.integer = stackPop(stack)->data.integer * stackPop(stack)->data.integer;
        } else {
            result->data.real = realLeftValue * realRightValue;
        }
    }
    else if (expression->type == GREATER){
        if (result->type == INTEGER){
            result->data.boolean = stackPop(stack)->data.integer > stackPop(stack)->data.integer;
        } else {
            result->data.boolean = realLeftValue > realRightValue;
        }
        result->type = BOOLEAN;
    }
    else if (expression->type == GREATER_OR_EQUALS){
        if (result->type == INTEGER){
            result->data.boolean = stackPop(stack)->data.integer >= stackPop(stack)->data.integer;
        } else {
            result->data.boolean = realLeftValue >= realRightValue;
        }
        result->type = BOOLEAN;
    }
    else if (expression->type == LESSER){
        if (result->type == INTEGER){
            result->data.boolean = stackPop(stack)->data.integer < stackPop(stack)->data.integer;
        } else {
            result->data.boolean = realLeftValue < realRightValue;
        }
        result->type = BOOLEAN;
    }
    else if (expression->type == LESSER_OR_EQUALS){
        if (result->type == INTEGER){
            result->data.boolean = stackPop(stack)->data.integer <= stackPop(stack)->data.integer;
        } else {
            result->data.boolean = realLeftValue <= realRightValue;
        }
        result->type = BOOLEAN;
    }

    stackPush(stack, result);

//     if (expression->type == NOT){
//         struct VariableValue* result = malloc(sizeof(struct VariableValue));
//         result->type = BOOLEAN;
//         result->data.boolean = !resolveExpression(namespace, expression->right);
//         return result;
//     }

//     struct VariableValue* left = resolveExpression(namespace, expression->left);
//     struct VariableValue* right = resolveExpression(namespace, expression->right);
//     struct VariableValue* result = malloc(sizeof(struct VariableValue));

//     float leftValue = left->type == REAL? left->data.real:left->data.integer;
//     float rightValue = right->type == REAL? right->data.real:right->data.integer;

//     if (expression->type == DIVISION){
//       result->type = REAL;
//       result->data.real = leftValue / rightValue;
//         return result;
//     };

//     if (left->type == REAL || right->type == REAL){
//         result->type = REAL;
//     } else {
//         result->type = INTEGER;
//     }

//     switch (expression->type) {
//         case ADDITION:
//             if (result->type == REAL){
//                 result->data.real = leftValue + rightValue;
//                 break;
//             }
//             result->data.integer = (int)(leftValue + rightValue);
//             break;

//         case SUBTRACTION:
//             if (result->type == REAL){
//                 result->data.real = leftValue - rightValue;
//                 break;
//             }
//             result->data.integer = (int)(leftValue - rightValue);
//             break;

//         case MULTIPLICATION:
//             if (result->type == REAL){
//                 result->data.real = leftValue * rightValue;
//                 break;
//             }
//             result->data.integer = (int)(leftValue * rightValue);
//             break;

//         case EQUALS:
//             result->type = BOOLEAN;
//             result->data.boolean = (float)(leftValue) == (float)(rightValue);
//             break;

//         case NOT_EQUALS:
//             result->type = BOOLEAN;
//             result->data.boolean = (float)(leftValue) != (float)(rightValue);
//             break;

//         case GREATER:
//             result->type = BOOLEAN;
//             result->data.boolean = (float)(leftValue) > (float)(rightValue);
//             break;

//         case GREATER_OR_EQUALS:
//             result->type = BOOLEAN;
//             result->data.boolean = (float)(leftValue) >= (float)(rightValue);
//             break;

//         case LESSER:
//             result->type = BOOLEAN;
//             result->data.boolean = (float)(leftValue) < (float)(rightValue);
//             break;

//         case LESSER_OR_EQUALS:
//             result->type = BOOLEAN;
//             result->data.boolean = (float)(leftValue) <= (float)(rightValue);
//             break;

//         case AND:
//             result->type = BOOLEAN;
//             result->data.boolean = left->data.boolean && right->data.boolean;
//             break;

//         case OR:
//             result->type = BOOLEAN;
//             result->data.boolean = left->data.boolean || right->data.boolean;
//             break;
//     }
//     return result;
 }
