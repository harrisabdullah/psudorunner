#include "../pseudo_std/std.h"
#include "../Parser/Expression.h"
#include "../common/List.h"
#include "../common/Stack.h"
#include "Variable.h"
#include <string.h>

void execSTDFunc(struct FuncCall f, List* ns, struct Stack* stack){
   for (int i=0; i<STD_FUNC_COUNT; i++){
      if (strcmp(f.lexeme, STD_FUNC_IDENTIFIERS[i]) != 0){
         continue;
      }
      STD_FUNCS[i](f.args, stack, ns);
      return;
   }
}
