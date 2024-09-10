//
// Created by Harris on 10/06/2024.
//

#include "Stack.h"
#include "tokenTypeToString.h"
#include "../ExecutionEngine/Variable.h"
#include "tokenTypeToString.h"
#include <stdlib.h>
#include <stdio.h>

void stackInit(struct Stack* stack){
   stack->arrayLength = STACK_CHUNK_SIZE;
   stack->head = 0;
   stack->popDepth = 0;
   stack->array = (struct VariableValue**)calloc(STACK_CHUNK_SIZE, sizeof(struct VariableValue*));


   if (stack->array == NULL){
      perror("stack allocation failed\n");
      exit(EXIT_FAILURE);
   }   
}

void stackPush(struct Stack* stack, struct VariableValue* data){
   if (stack->head == stack->arrayLength){
      stack->arrayLength += STACK_CHUNK_SIZE;
      stack->array = (struct VariableValue**)realloc(stack->array, sizeof(struct VariableValue*)*stack->arrayLength);

      if (stack->array == NULL){
         perror("stack allocation failed\n");
         exit(EXIT_FAILURE);
      }
   }

   if (stack->popDepth >= 1){
      // freeVariable(stack->array[stack->head]);
      stack->popDepth--;
   }

   stack->array[stack->head] = data;
   stack->head++;
}

struct VariableValue* stackPop(struct Stack* stack){
   if (stack->arrayLength - stack->head >= 2 * STACK_CHUNK_SIZE){
      stack->arrayLength -= STACK_CHUNK_SIZE;
      stack->array = (struct VariableValue**)realloc(stack->array, sizeof(struct VariableValue*)*stack->arrayLength);
   };

   stack->head--;
   stack->popDepth++;
   return stack->array[stack->head];
}

enum TokenType stackTypePeek(struct Stack* stack, int headOffset){
   return stack->array[stack->head-1-headOffset]->type;
}

void printStack(struct Stack stack){
   printf("stack: {");
   for (int i=0; i<stack.head; i++){
      printf("(type: %s, type: ", tokenTypeToString(stack.array[i]->type));
      switch (stack.array[i]->type){
         case INTEGER:
            printf("%d", stack.array[i]->data.integer);
            break;
         case BOOLEAN:
            printf("%d", stack.array[i]->data.boolean);
            break;
         case REAL:
            printf("%f", stack.array[i]->data.real);
            break;
      }
      printf(")\n");
   }
   printf("}\n");
}

