cmake_minimum_required(VERSION 3.20)

set(ProjectName Example)

project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Node.hpp
)

set(Source
    Node.cpp
)

add_library(${ProjectName} STATIC ${Source} ${Headers})

add_subdirectory(test)
