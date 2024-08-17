//
// Created by Harris on 09/04/2024.
//

#include "Namespace.h"
#include "Resolver.h"
#include "../common/Stack.h"
#include "../common/tokenTypeToString.h"
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
void namespaceAssign(struct List* namespace, struct Identifier identifier, struct Expression* data, struct Stack* stack){
    int i = 0;
    while (i < namespace->head && strcmp(namespace->array[i].variable.variableName, identifier.lexeme) != 0){
        i++;
    }
    if (i >= namespace->head){
        // TODO: explode
        printf("cant find name to assign too\n");
        return;
    }

    resolveExpression(namespace, data, stack);
    struct VariableValue* resolvedValue = stackPop(stack);
    if (identifier.hasIndex){
        resolveExpression(namespace, identifier.indexExpression, stack);
        int index = stackPop(stack)->data.integer;
        char c = resolvedValue->data.string[0];
        namespace->array[i].variable.value->data.string[index-1] = c;
        return;
    }
    namespace->array[i].variable.value = resolvedValue;

}


