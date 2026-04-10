cmake_minimum_required(VERSION 3.5)
project(Homework4)

set(CMAKE_CXX_STANDARD 20)

# Fetch doctest
include(FetchContent)
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.12  # Use the latest stable version
)
FetchContent_MakeAvailable(doctest)

# Enable testing
enable_testing()

add_executable(Exe src/main.cpp)
add_executable(Test test/tests.cpp)
add_library(Lib
        include/Entry.h
        include/Node.h
        include/FileUtils.h
        include/BinarySearchTree.h
        src/FileUtils.cpp
        src/BinarySearchTree.cpp)
target_link_libraries(Exe PRIVATE Lib)
target_link_libraries(Test PRIVATE Lib doctest::doctest)

add_test(NAME PhonebookTests COMMAND Test)