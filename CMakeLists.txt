cmake_minimum_required(VERSION 3.23)
project(psudo_interprator_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(psudo_interprator_2 main.c Parser.c Parser.h AST.c AST.h Tokenisation/Tokenizer.c Tokenisation/Tokenizer.h Tokenisation/TokensList.c Tokenisation/TokensList.h)
