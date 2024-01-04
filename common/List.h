//
// Created by Harris on 03/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_LIST_H
#define PSUDO_INTERPRATOR_2_LIST_H

#define ARRAY_SIZE 50

#include "../Tokenisation/Token.h"
#include <stdio.h>

enum listValueType {
    TOKEN
};

union listValue {
    struct Token token;
};

struct List {
    size_t length;
    int head;
    enum listValueType type;
    union listValue* array;
};

struct List* listInit(enum listValueType type);
void listAppend(struct List* list, union listValue item);
union listValue* listGetLastItem(struct List* list);

// TODO
// void printList(struct list* tokenList);

#endif //PSUDO_INTERPRATOR_2_LIST_H
