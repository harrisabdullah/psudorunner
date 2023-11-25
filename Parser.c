//
// Created by Harris on 19/11/2023.
//

#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

struct ASTNode* parseFile(const char* filename){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    struct ASTNode* head;
    struct ASTNode* currant;


    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    if ((read = getline(&line, &len, fp)) != -1){
        head = parseLine(line, read, NULL);
        currant = head;
    }
    else {
        return NULL;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        currant = parseLine(line, read, currant);
    }

    fclose(fp);
    if (line)
        free(line);

    return head;
};

struct ASTNode* parseLine(const char* line, ssize_t length, struct ASTNode* previous){

};