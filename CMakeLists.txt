cmake_minimum_required(VERSION 3.23)
project(psudo_interprator_2 C)

set(CMAKE_C_STANDARD 99)

include(cmake/updateSubmodules.cmake)
add_executable(psudo_interprator_2 main.c Tokenisation/Tokenizer.c Tokenisation/Tokenizer.h common/List.c common/List.h Tokenisation/Token.h Parser/Parser.c Parser/Parser.h Parser/ASTNode.h Parser/Expression.h common/tokenTypeToString.c common/tokenTypeToString.h ExecutionEngine/ExecutionEngine.c ExecutionEngine/ExecutionEngine.h ExecutionEngine/Namespace.c ExecutionEngine/Namespace.h ExecutionEngine/Resolver.c ExecutionEngine/Resolver.h ExecutionEngine/Variable.h common/Stack.h common/Stack.c Parser/parseAssignment.c Parser/parseDeclare.c Parser/parseElse.c Parser/parseIf.c Parser/parseOutput.c Parser/parseWhile.c)
