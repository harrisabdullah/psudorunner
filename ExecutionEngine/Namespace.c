//
// Created by Harris on 09/04/2024.
//

#include "Namespace.h"
#include "Resolver.h"
#include "../common/Stack.h"
#include <stdlib.h>
#include <string.h>

/**
 * Initializes a new namespace list.
 *
 * @return: A pointer to the newly created namespace list.
 */
struct List* namespaceInit(){
    return listInit(Variable);
}

/**
 * Appends a new variable to the namespace list.
 *
 * @param namespaceList: The namespace list to append to.
 * @param identifier: The name of the variable to append.
 * @param type: The type of the variable to append.
 *
 * @return: None
 */
void namespaceAppend(struct List* namespaceList, char* identifier, enum TokenType type){
    struct VariableValue* value = (struct VariableValue*) malloc(sizeof(struct VariableValue));
    value->type = type;
    value->data = (union VariableData){};

    listAppend(namespaceList, (union listValue){.variable=(struct Variable){
        .variableName = identifier,
        .value = value,
    }});
}

/**
 * Assigns a new value to a variable in the namespace list.
 *
 * @param namespaceList: The namespace list to search for the variable.
 * @param identifier: The name of the variable to assign a value to.
 * @param data: The new value to assign to the variable.
 *
 * @return: None
 */
void namespaceAssign(struct List* namespaceList, char* identifier, struct Expression* data, struct Stack* stack){
    for (int i=0; i<namespaceList->head;i++){
        if (strcmp(namespaceList->array[i].variable.variableName, identifier) == 0){
            resolveExpression(namespaceList, data, stack);
            namespaceList->array[i].variable.value = stackPop(stack);
            return;
        }
    }
}


