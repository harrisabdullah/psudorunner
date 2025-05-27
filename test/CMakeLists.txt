cmake_minimum_required(VERSION 3.29)

set(This Tests)

set(Sources
    tokentest.cpp
)

add_executable(${This} ${Sources})

target_include_directories(${This} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${This} PUBLIC
    gtest_main
    psudo_interprator
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
