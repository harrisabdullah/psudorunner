//
// Created by Harris on 03/01/2024.
//

#include "List.h"
#include <stdlib.h>

/**
 * Initializes a list of a given data type.
 *
 * @param type: the data type of items that will be contained in the list
 * @return: a pointer to an empty struct List
 */
struct List* listInit(enum listValueType type){
    struct List* newList = malloc(sizeof(struct List));

    if (newList == NULL) {
        perror("Allocation Error: unable to allocate List");
        exit(EXIT_FAILURE);
    }

    newList->type = type;
    newList->head = 0;
    newList->length = ARRAY_SIZE;

    newList->array = malloc(sizeof(union listValue) * ARRAY_SIZE);

    return newList;
}

/**
 * Appends an item to a list.
 *
 * @param list: a pointer to the list to which an item will be appended.
 * @param item: the item to be appended.
 */
void listAppend(struct List* list, union listValue item){
    if (list->head >= list->length){
        list->length += ARRAY_SIZE;
        list->array = realloc(list->array, sizeof(union listValue) * list->length);

        if (list->array == NULL) {
            perror("Allocation Error: unable to reallocate List");
            exit(EXIT_FAILURE);
        }
    }

    list->array[list->head] = item;
    list->head++;
}

/**
 * Gets the last item of a list.
 *
 * @param list: a pointer to the list
 * @return: the last item of the list.
 */
union listValue* listGetLastItem(struct List* list){
    if (list->head <= 0){
        perror("IndexError: trying to access the previous element of an empty list. ");
        exit(EXIT_FAILURE);
    }

    return &list->array[list->head - 1];
}

/**
* Pops last item out of a list.
*
* @param list: a pointer to the list.
* @return: the popped value.
*/
union listValue* listPop(struct List* list){
    union listValue* value = listGetLastItem(list);
    list->head--;
    return value;    
}