#include "std.h"

void std_INT(List args, struct Stack* stack, List* ns){
   resolveExpression(ns, (struct Expression*)args.items[0], stack);
   struct VariableValue* arg = stackPop(stack);
   struct VariableValue* ret = malloc(sizeof(struct VariableValue));
   if (ret == NULL){
      ie_allocationError();
   }

   ret->type = INTEGER;
   if (arg->type == REAL){
      ret->data.integer = (int)arg->data.real;
      stackPush(stack, ret);
      return;
   }
   if (arg->type == STRING){
      // TODO: is digit check
      ret->data.integer = atoi(arg->data.string);
      stackPush(stack, ret);
      return;
   }
   // TODO: type error
}