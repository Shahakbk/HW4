cmake_minimum_required(VERSION 3.7)
project(HW4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG")

set(SOURCE_FILES Wet/Exceptions.h Wet/Enigma.cpp Wet/Enigma.h
        Wet/EscapeRoomWrapper.cpp Wet/EscapeRoomWrapper.h Wet/EscapeRoom.c
        Wet/list.h Wet/mtmtest.h Wet/ScaryRoom.cpp Wet/ScaryRoom.h
        Wet/KidsRoom.cpp Wet/KidsRoom.h Wet/Company.cpp Wet/Company.h
        Wet/tests/list_test.cpp)
add_executable(HW4 ${SOURCE_FILES})