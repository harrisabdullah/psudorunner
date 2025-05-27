//
// Created by Harris on 09/04/2024.
//

#include "Namespace.h"
#include "Resolver.h"
#include "../common/Stack.h"
#include "../common/tokenTypeToString.h"
#include "../errors/internalErrors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

List* namespaceInit(){
    List* namespace = malloc(sizeof(List));
    listInit(namespace);
    return namespace;
}

void namespaceAppend(List* namespaceList, char* identifier, enum TokenType type){
    
    struct VariableValue* value = malloc(sizeof(struct VariableValue));
    Variable* var = malloc(sizeof(Variable));
    if (value == NULL || var == NULL){
        ie_allocationError();
    }
    value->type = type;
    var->value = value;
    var->variableName = identifier;

    listAppend(namespaceList, var);
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
void namespaceAssign(List* namespace, struct Identifier identifier, struct Expression* data, struct Stack* stack){
    int i = 0;
    while (i < namespace->length && strcmp(((Variable*)namespace->items[i])->variableName, identifier.lexeme) != 0){
        i++;
    }
    if (i >= namespace->length){
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
        ((Variable*)namespace->items[i])->value->data.string[index-1] = c;
        return;
    }
    ((Variable*)namespace->items[i])->value = resolvedValue;
}


