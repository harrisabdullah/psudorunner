//
// Created by Harris on 15/08/2024.
//
#include "Resolver.h"
#include <String.h>

void resolveIdentifier(struct List* namespace, struct Identifier identifier, struct Stack* stack){
   struct VariableValue* value;
   for (int i=0; i<namespace->head; i++){
      if (strcmp(identifier.lexeme, namespace->array[i].variable.variableName) == 0){
            value = namespace->array[i].variable.value;
            break;
      }
   }
   if (!identifier.hasIndex){
      stackPush(stack, value);
      return;
   }

   struct VariableValue* returnValue = (struct VariableValue*)malloc(sizeof(struct VariableValue));

   resolveExpression(namespace, identifier.indexExpression, stack);
   int index = stackPop(stack)->data.integer;

   returnValue->type = CHARACTER;
   returnValue->data.character = value->data.string[index-1];
   stackPush(stack, returnValue);
};