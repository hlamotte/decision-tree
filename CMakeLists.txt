cmake_minimum_required(VERSION 3.20)

set(ProjectName DecisionTree)

project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Node.hpp
    CSVReader.hpp
    DecisionTree.hpp
)

set(Source
    Node.cpp
    CSVReader.cpp
    DecisionTree.cpp
    Main.cpp
)

add_library(${ProjectName} SHARED ${Source} ${Headers})

add_subdirectory(test)
