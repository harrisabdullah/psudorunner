cmake_minimum_required(VERSION 3.23)

set(This psudo_interprator)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(SRC
    src/main.c
    src/Tokenisation/Tokenizer.c
    src/common/List.c
    src/common/tokenTypeToString.c
    src/ExecutionEngine/ExecutionEngine.c
    src/ExecutionEngine/resolveIdentifier.c
    src/ExecutionEngine/Namespace.c
    src/ExecutionEngine/Resolver.c
    src/ExecutionEngine/execSTDFunc.c
    src/common/Stack.c
    src/Parser/Parser.c
    src/Parser/parseAssignment.c
    src/Parser/parseDeclare.c
    src/Parser/parseElse.c
    src/Parser/parseIf.c
    src/Parser/parseOutput.c
    src/Parser/parseWhile.c
    src/Parser/parseRepeat.c
    src/Parser/parseFor.c
    src/Parser/parseFuncCall.c
    src/errors/internalErrors.c
    src/errors/errors.c
    src/errors/syntaxChecker.c
    src/errors/parserErrors.c
    src/pseudo_std/std_INT.c
    src/pseudo_std/std.c
)

set(HDR
    src/Tokenisation/Tokenizer.h
    src/Tokenisation/Token.h
    src/common/List.h
    src/common/tokenTypeToString.h
    src/ExecutionEngine/ExecutionEngine.h
    src/ExecutionEngine/Namespace.h
    src/ExecutionEngine/Resolver.h
    src/ExecutionEngine/Variable.h
    src/common/Stack.h
    src/Parser/Parser.h
    src/Parser/ASTNode.h
    src/Parser/Expression.h
    src/errors/internalErrors.h
    src/errors/syntaxChecker.h
    src/errors/parserErrors.h
    src/errors/errors.h
    src/pseudo_std/std.h
)

add_library(${This} STATIC
    ${SRC}
)

add_subdirectory(test)