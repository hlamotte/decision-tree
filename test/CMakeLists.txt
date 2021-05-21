cmake_minimum_required(VERSION 3.20)

set(ProjectName DecisionTests)

set(Sources
    #NodeTests.cpp
    CSVReaderTests.cpp
    #DecisionTreeTests.cpp
)

add_executable(${ProjectName} ${Sources})

target_link_libraries(${ProjectName} PUBLIC
    gtest_main
    DecisionTree
)

add_test(
    NAME ${ProjectName}
    COMMAND ${ProjectName}
)