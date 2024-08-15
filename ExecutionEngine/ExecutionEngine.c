//
// Created by Harris on 09/04/2024.
//

#include "ExecutionEngine.h"
#include "../common/Stack.h"
#include "../common/tokenTypeToString.h"
#include "Namespace.h"
#include "Variable.h"
#include "Resolver.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Executes the Abstract Syntax Tree (AST) represented by ASTList.
 *
 * @param ASTList: The list representing the AST to execute.
 *
 * @return: None
 */
struct List* executeAST(struct List* ASTList, struct List* namespace){
    struct Stack* stack = calloc(1, sizeof(struct Stack));

    if (stack == NULL){
        perror("allocation failure\n");
        exit(EXIT_FAILURE);
    }

    stackInit(stack);
    struct VariableValue* temp;
    for (int i=0; i<ASTList->head; i++){
        switch (ASTList->array[i].astNodeValue.type) {
            case DECLARE:
                namespaceAppend(namespace,
                                ASTList->array[i].astNodeValue.value.declare.identifier,
                                ASTList->array[i].astNodeValue.value.declare.type);
                break;
            case ASSIGNMENT:
                namespaceAssign(namespace,
                                ASTList->array[i].astNodeValue.value.assignment.identifier,
                                ASTList->array[i].astNodeValue.value.assignment.value,
                                stack);
                break;
            case OUTPUT:
                resolveExpression(namespace,
                                  ASTList->array[i].astNodeValue.value.output.value,
                                  stack);
                temp = stackPop(stack);

                if (temp->type == INTEGER){
                    printf("%d\n", temp->data.integer);
                }
                else if (temp->type == REAL){
                    printf("%f\n", temp->data.real);
                }
                else if (temp->type == BOOLEAN){
                    printf("%s\n", temp->data.boolean? "TRUE":"FALSE");
                }
                else if (temp->type == STRING){
                    printf("%s\n", temp->data.string);
                }
                else if (temp->type == CHARACTER){
                    printf("%c\n", temp->data.character);
                }
                break;

            case IF:
                resolveExpression(namespace, ASTList->array[i].astNodeValue.value.If.test, stack);
                temp = stackPop(stack);
                if (temp->data.boolean){
                    namespace = executeAST(ASTList->array[i].astNodeValue.value.If.content, namespace);
                }
                else if (i+1 < ASTList->head && ASTList->array[i+1].astNodeValue.type == ELSE) {
                    namespace = executeAST(ASTList->array[i+1].astNodeValue.value.Else.content, namespace);
                    i++;
                }
                break;

            case WHILE:
                resolveExpression(namespace, ASTList->array[i].astNodeValue.value.While.condition, stack);
                while (stackPop(stack)->data.boolean){
                    executeAST(ASTList->array[i].astNodeValue.value.While.content, namespace);
                    resolveExpression(namespace, ASTList->array[i].astNodeValue.value.While.condition, stack);
                }
                break;
            
            case REPEAT:
                do {
                    executeAST(ASTList->array[i].astNodeValue.value.Repeat.content, namespace);
                    resolveExpression(namespace, ASTList->array[i].astNodeValue.value.Repeat.condition, stack);
                } while (!stackPop(stack)->data.boolean);
                break;
            
            case FOR:
                namespaceAssign(namespace, ASTList->array[i].astNodeValue.value.For.identifier,
                                           ASTList->array[i].astNodeValue.value.For.rangeMin, stack);
                struct Expression condition;
                struct Expression identifierGetter;
                struct Expression increment;
                struct Expression one;
                identifierGetter.type = IDENTIFIER;
                identifierGetter.isConstant = 1;
                identifierGetter.lexeme = ASTList->array[i].astNodeValue.value.For.identifier;

                condition.type = GREATER_OR_EQUALS;
                condition.isConstant = 0;
                condition.left = &identifierGetter;
                condition.right = ASTList->array[i].astNodeValue.value.For.rangeMax;

                one.type = INTEGER;
                one.isConstant = 1;
                one.lexeme = "1";

                increment.type = ADDITION;
                increment.isConstant = 0;
                increment.left = &identifierGetter;
                increment.right = &one;
                resolveExpression(namespace, &condition, stack);
                while (!stackPop(stack)->data.boolean){
                    executeAST(ASTList->array[i].astNodeValue.value.For.content, namespace);
                    namespaceAssign(namespace, ASTList->array[i].astNodeValue.value.For.identifier, &increment, stack);
                    resolveExpression(namespace, &condition, stack);
                }   
                break;
      ;  }
    }
    return namespace;
}
