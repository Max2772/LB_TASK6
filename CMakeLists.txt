cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(SOURCE_FILES main.c funcs.c)

add_subdirectory(googletest)

add_executable(app main.c)
add_executable(test tests/tests.cpp)
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(test gtest gtest_main)

