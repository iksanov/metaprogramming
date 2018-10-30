cmake_minimum_required(VERSION 3.8)
project(Patterns_Metaprogramming)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp mediator.cpp mediator.h observer.h observer.cpp proxy.h proxy.cpp template_classes.h)
add_executable(Patterns_Metaprogramming ${SOURCE_FILES})