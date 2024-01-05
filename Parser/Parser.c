//
// Created by Harris on 05/01/2024.
//

#include "../common/List.h"
#include "Parser.h"
#include "ASTNode.h"

struct List* parse(struct List* tokens){
    struct List* ASTList = listInit(ASTNode);
    // Two indexes that form an inclusive range representing the currant line of code.
    int start = 0;
    int end = 0;

    while (end < tokens->head){
        // Moving to the next line of code.
        end += 2; // Skipping over the previous TK_NEW_LINE.
        start = end;

        while (end < tokens->head && tokens->array[end].tokenValue.type != TK_NEW_LINE){
            end++;
        }
        // If this line is empty. i.e. two new lines next to each other or a newline then EOF.
        if (start == end){
            continue;
        }

        struct ASTNode newNode;
        switch (tokens->array[start].tokenValue.type) {
            case TK_DECLARE:
                newNode.type = AST_DECLARE;
                newNode.value.declare = (struct ASTDeclare){.type=};
        }
    }
};