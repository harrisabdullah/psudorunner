cmake_minimum_required(VERSION 3.23)
project(psudo_interprator_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(psudo_interprator_2 main.c Tokenisation/Tokenizer.c Tokenisation/Tokenizer.h common/List.c common/List.h Tokenisation/Token.h Parser/Parser.c Parser/Parser.h Parser/ASTNode.h Parser/Expression.h common/tokenTypeToString.c common/tokenTypeToString.h)
