//
// Created by Harris on 09/04/2024.
//

#include "Resolver.h"
#include <stdlib.h>
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
                return namespace->array[i].variable.value;
            }
        }
    }
    struct VariableValue* result = malloc(sizeof(struct VariableValue));
    if (!result) {
        // Handle allocation failure
        return NULL;
    }

    result->type = type;

    switch(type) {
        case REAL:
            result->data.real = atof(data);
            break;
        case INTEGER:
            result->data.integer = atoi(data);
            break;
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
struct VariableValue* resolveExpression(struct List* namespace, struct Expression* expression){
    if (expression->isConstant){
        return stringToVariableValue(expression->type, expression->lexeme, namespace);
    }
    struct VariableValue* left = resolveExpression(namespace, expression->left);
    struct VariableValue* right = resolveExpression(namespace, expression->right);
    struct VariableValue* result = malloc(sizeof(struct VariableValue));

    float leftValue = left->type == REAL? left->data.real:left->data.integer;
    float rightValue = right->type == REAL? right->data.real:right->data.integer;

    if (left->type == REAL || right->type == REAL){
        result->type = REAL;
    } else {
        result->type = INTEGER;
    }

    switch (expression->type) {
        case ADDITION:
            if (result->type == REAL){
                result->data.real = leftValue + rightValue;
                break;
            }
            result->data.integer = (int)(leftValue + rightValue);
            break;

        case SUBTRACTION:
            if (result->type == REAL){
                result->data.real = leftValue - rightValue;
                break;
            }
            result->data.integer = (int)(leftValue - rightValue);
            break;

        case MULTIPLICATION:
            if (result->type == REAL){
                result->data.real = leftValue * rightValue;
                break;
            }
            result->data.integer = (int)(leftValue * rightValue);
            break;

        case DIVISION:
            if (result->type == REAL){
                result->data.real = leftValue / rightValue;
                break;
            }
            result->data.integer = (int)(leftValue / rightValue);
            break;
    }
    return result;
}
