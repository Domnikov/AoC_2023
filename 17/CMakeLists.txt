cmake_minimum_required (VERSION 3.5)
project("app")

set(CMAKE_CXX_STANDARD 20)

if(DEFINED TEST)
    add_compile_definitions(TEST)
endif()

add_executable(${PROJECT_NAME} main.cpp)
