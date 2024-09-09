//
// Created by Harris on 03/01/2024.
//

#ifndef PSUDO_INTERPRATOR_2_LIST_H
#define PSUDO_INTERPRATOR_2_LIST_H

#include <stdlib.h>
#define LIST_BUFFER_SIZE 20
#define LIST_BUFFER_LIMIT 30

typedef struct List {
   int length;
   void** items;
   size_t allocated;
} List;

void listInit(List* list);
void listAppend(List* list, void* value);
void* listPeek(List* list);
void* listPop(List* list);
void listFree(List* list);

#endif //PSUDO_INTERPRATOR_2_LIST_H
