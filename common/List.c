//
// Created by Harris on 03/01/2024.
//
#include "../errors/internalErrors.h"
#include "List.h"
#include <stdio.h>

void listInit(List* list){
   list->length = 0;
   list->allocated = LIST_BUFFER_SIZE;
   list->items = (void**) malloc(LIST_BUFFER_SIZE * sizeof(void*));
   if (list->items == NULL){
      ie_allocationError();
   }
}

void listAppend(List* list, void* value){
   if (list->length >= list->allocated){
      list->allocated += LIST_BUFFER_SIZE;
      list->items = (void**)realloc(list->items, list->allocated * sizeof(void*));
      if (list->items == NULL){
         ie_allocationError();
      }
   }
   list->items[list->length] = value;
   list->length++;
}

void* listPeek(List* list){
   return list->items[list->length - 1];
}

void* listPop(List* list){
   list->length--;
   if (list->allocated - list->length >= LIST_BUFFER_LIMIT){
      list->allocated = list->length + LIST_BUFFER_SIZE;
      list->items = (void**)realloc(list->items, list->allocated * sizeof(void*));
      if (list->items == NULL){
         ie_allocationError();
      }
   }
   return list->items[list->length];
}

void listFree(List* list){
   free(list->items);
   list->items = NULL;
   list->length = 0;
   list->allocated = 0;
}