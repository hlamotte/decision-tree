cmake_minimum_required(VERSION 3.20)

set(ProjectName DecisionTree)

project(${ProjectName} CXX)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# require C++11
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x  -stdlib=libc++") 

add_compile_options(-O3 -Wall)

enable_testing()

add_subdirectory(googletest)

set(Headers
    #Node.hpp
    CSVReader.hpp
    #DecisionTree.hpp
)

set(Source
    #Node.cpp
    CSVReader.cpp
    #DecisionTree.cpp
    #Main.cpp
)

add_library(${ProjectName} SHARED ${Source} ${Headers})

add_subdirectory(test)
