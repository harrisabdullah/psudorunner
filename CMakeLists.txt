cmake_minimum_required(VERSION 3.23)
project(psudo_interprator_2 C)

set(CMAKE_C_STANDARD 99)

# Include the script for updating submodules
include(cmake/updateSubmodules.cmake)

# Set the source files for the project
set(SOURCES
    main.c
    Tokenisation/Tokenizer.c
    common/List.c
    common/tokenTypeToString.c
    ExecutionEngine/ExecutionEngine.c
    ExecutionEngine/resolveIdentifier.c
    ExecutionEngine/Namespace.c
    ExecutionEngine/Resolver.c
    common/Stack.c
    Parser/Parser.c
    Parser/parseAssignment.c
    Parser/parseDeclare.c
    Parser/parseElse.c
    Parser/parseIf.c
    Parser/parseOutput.c
    Parser/parseWhile.c
    Parser/parseRepeat.c
    Parser/parseFor.c
    errors/internalErrors.c
)

# Set the header files (optional but helpful)
set(HEADERS
    Tokenisation/Tokenizer.h
    Tokenisation/token.h
    common/List.h
    common/tokenTypeToString.h
    ExecutionEngine/ExecutionEngine.h
    ExecutionEngine/Namespace.h
    ExecutionEngine/Resolver.h
    ExecutionEngine/Variable.h
    common/Stack.h
    Parser/Parser.h
    Parser/ASTNode.h
    Parser/Expression.h
    errors/internalErrors.h
)

# Add executable target
add_executable(psudo_interprator_2 ${SOURCES} ${HEADERS})
