cmake_minimum_required(VERSION 3.7)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

SET(GXX_COVERAGE_COMPILE_FLAGS "-Wall -pedantic-errors -Werror -DNDEBUG")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GXX_COVERAGE_COMPILE_FLAGS}" )

set(SOURCE_FILES Wet/Enigma.cpp Wet/list.h Wet/tests/ListTest.cpp)
add_executable(HW4 ${SOURCE_FILES})

