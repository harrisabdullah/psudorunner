//
// Created by Harris on 09/04/2024.
//

#include "ExecutionEngine.h"
#include "Namespace.h"
#include "Variable.h"
#include "Resolver.h"

/**
 * Executes the Abstract Syntax Tree (AST) represented by ASTList.
 *
 * @param ASTList: The list representing the AST to execute.
 *
 * @return: None
 */
struct List* executeAST(struct List* ASTList, struct List* namespace){
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
                                ASTList->array[i].astNodeValue.value.assignment.value);
                break;
            case OUTPUT:
                temp = resolveExpression(namespace,
                                         ASTList->array[i].astNodeValue.value.output.value);
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
                temp = resolveExpression(namespace, ASTList->array[i].astNodeValue.value.If.test);
                if (temp->data.boolean){
                    namespace = executeAST(ASTList->array[i].astNodeValue.value.If.content, namespace);
                }
      ;  }
    }
}
