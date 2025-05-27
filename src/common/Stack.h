//
// Created by Harris on 10/06/2024.
//

#ifndef PSUDO_INTERPRATOR_2_STACK_H
#define PSUDO_INTERPRATOR_2_STACK_H
#include "../ExecutionEngine/Variable.h"
#include "../Tokenisation/Token.h"
#include "../Parser/ASTNode.h"
#define STACK_CHUNK_SIZE 32
#define MAX_STACK_SIZE 1024

struct Stack {
   size_t arrayLength;
   int head;
   int popDepth;
   struct VariableValue** array;
};

void stackInit(struct Stack* stack);
void stackPush(struct Stack* stack, struct VariableValue* data);
enum TokenType stackTypePeek(struct Stack* stack, int headOffset);
struct VariableValue* stackPop(struct Stack* stack);


#endif