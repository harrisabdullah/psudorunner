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
                break;

            case IF:
                resolveExpression(namespace, ASTList->array[i].astNodeValue.value.If.test, stack);
                temp = stackPop(stack);
                if (temp->data.boolean){
                    namespace = executeAST(ASTList->array[i].astNodeValue.value.If.content, namespace);
                }
      ;  }
    }
    return namespace;
}
