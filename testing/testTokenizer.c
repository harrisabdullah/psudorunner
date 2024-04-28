//
// Created by Harris on 28/04/2024.
//

#include "../Tokenisation/Token.h"
#include "testTokenizer.h"
#include <stdlib.h>
#include <string.h>
#include "../Tokenisation/Tokenizer.h"


void testTokenizer(){
    printf("----------\nTEST_INPUT: 'DECLARE i: INTEGER\\nDECLARE j: REAL\\nDECLARE test_test-test22: BOOLEAN', 68\n");
    struct List* outputTokens = tokenize("DECLARE i: INTEGER\nDECLARE j: REAL\nDECLARE test_test-test22: BOOLEAN", 68);
    struct Token test[] = {{DECLARE, ""},
                           {IDENTIFIER, "i"},
                           {COLON, ""},
                           {INTEGER_IDENTIFIER, ""},
                           {NEW_LINE, ""},

                           {DECLARE, ""},
                           {IDENTIFIER, "j"},
                           {COLON, ""},
                           {REAL_IDENTIFIER, ""},
                           {NEW_LINE, ""},

                           {DECLARE, ""},
                           {IDENTIFIER, "test_test-test22"},
                           {COLON, ""},
                           {BOOLEAN_IDENTIFIER, ""},
                           };
    if (compareTokens(outputTokens, test, 14) == 0){
        printf("TEST FAILED");
        printTokenList(outputTokens);
        exit(1);
    }
    printf("TEST PASSED\n----------\n");

    // Second test
    printf("TEST_INPUT: 'j <- ((1.11+2) / 22  -2.000 *0 < 4 <= 7) > 1 >= 21 = 4 AND NOT TRUE OR FALSE', 76\n");
    outputTokens = tokenize("j <- ((1.11+2) / 22  -2.000 *0 < 4 <= 7) > 1 >= 21 = 4 AND NOT TRUE OR FALSE", 76);
    struct Token test2[] = {
            {IDENTIFIER, "j"},
            {ASSIGNMENT, ""},
            {OPEN_PAREN, ""},
            {OPEN_PAREN, ""},
            {REAL, "1.11"},
            {ADDITION, ""},
            {INTEGER, "2"},
            {CLOSE_PAREN, ""},
            {DIVISION, ""},
            {INTEGER, "22"},
            {SUBTRACTION, ""},
            {REAL, "2.000"},
            {MULTIPLICATION, ""},
            {INTEGER, "0"},
            {LESSER, ""},
            {INTEGER, "4"},
            {LESSER_OR_EQUALS, ""},
            {INTEGER, "7"},
            {CLOSE_PAREN, ""},
            {GREATER, ""},
            {INTEGER, "1"},
            {GREATER_OR_EQUALS, ""},
            {INTEGER, "21"},
            {EQUALS, ""},
            {INTEGER, "4"},
            {AND, ""},
            {NOT, ""},
            {BOOLEAN, "TRUE"},
            {OR, ""},
            {BOOLEAN, "FALSE"},
    };
    if (compareTokens(outputTokens, test2, 30) == 0){
        printf("TEST FAILED");
        printTokenList(outputTokens);
        exit(1);
    }
    printf("TEST PASSED\n----------\n");

    // test 3

    printf("TEST_INPUT: 'OUTPUT 1\\nIF TRUE THEN\\nOUTPUT 2\\nIF 1<1 THEN\\nOUTPUT 3\\nIF FALSE OR NOT TRUE THEN\\nOUTPUT 5\\nENDIF\\nENDIF\\nENDIF\\nIF 2 <= 9 THEN\\ni <- i\\nENDIF', 132\n");
    outputTokens = tokenize("OUTPUT 1\nIF TRUE THEN\nOUTPUT 2\nIF 1<1 THEN\nOUTPUT 3\nIF FALSE OR NOT TRUE THEN\nOUTPUT 5\nENDIF\nENDIF\nENDIF\nIF 2 <= 9 THEN\ni <- i\nENDIF", 132);
    struct Token test3[] = {
            {OUTPUT, ""},
            {INTEGER, "1"},
            {NEW_LINE, ""},

            {IF, ""},
            {BOOLEAN, "TRUE"},
            {THEN, ""},
            {NEW_LINE, ""},

            {OUTPUT, ""},
            {INTEGER, "2"},
            {NEW_LINE, ""},

            {IF, ""},
            {INTEGER, "1"},
            {LESSER, ""},
            {INTEGER, "1"},
            {THEN, ""},
            {NEW_LINE, ""},

            {OUTPUT, ""},
            {INTEGER, "3"},
            {NEW_LINE, ""},

            {IF, ""},
            {BOOLEAN, "FALSE"},
            {OR, ""},
            {NOT, ""},
            {BOOLEAN, "TRUE"},
            {THEN, ""},
            {NEW_LINE, ""},

            {OUTPUT, ""},
            {INTEGER, "5"},
            {NEW_LINE, ""},

            {ENDIF, ""},
            {NEW_LINE, ""},

            {ENDIF, ""},
            {NEW_LINE, ""},

            {ENDIF, ""},
            {NEW_LINE, ""},

            {IF, ""},
            {INTEGER, "2"},
            {LESSER_OR_EQUALS, ""},
            {INTEGER, "9"},
            {THEN, ""},
            {NEW_LINE, ""},

            {IDENTIFIER, "i"},
            {ASSIGNMENT, ""},
            {IDENTIFIER, "i"},
            {NEW_LINE, ""},

            {ENDIF, ""},
    };

    if (compareTokens(outputTokens, test3, 46) == 0){
        printf("TEST FAILED");
        printTokenList(outputTokens);
        exit(1);
    }
    printf("TEST PASSED\n----------\n");

    // insert more tests here
}

int compareTokens(struct List* tokens, struct Token test[], int length){
    for (int i=0; i<length; i++){
        if (tokens->array[i].tokenValue.type != test[i].type){
            return 0;
        }
        if (strcmp(tokens->array[i].tokenValue.lexeme, test[i].lexeme) != 0){
            return 0;
        }
    }
    return 1;
};