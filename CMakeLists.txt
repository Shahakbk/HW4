cmake_minimum_required(VERSION 3.7)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG")

set(SOURCE_FILES Wet/Exceptions.h Wet/tests/ListTest.cpp Wet/List.h)
add_executable(HW4 ${SOURCE_FILES})