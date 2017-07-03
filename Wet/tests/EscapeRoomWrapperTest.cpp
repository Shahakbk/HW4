//
// Created by adire on 30-Jun-17.
//
#include <iostream>

#include "../EscapeRoomWrapper.h"
#include "../Enigma.h"
#include "../Exceptions.h"
#include "mtmtest.h"

using namespace mtm::escaperoom;
using std::cout;
using std::endl;

void testWrapperCtor(){
    //test first ctor
    ASSERT_NO_THROW(EscapeRoomWrapper((char*)"room", 50, 8, 12));
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_EQUALS("room", room.getName());
    ASSERT_EQUALS(50, room.getMaxTime());
    ASSERT_EQUALS(8, room.level());
    ASSERT_EQUALS(12, room.getMaxParticipants());
    ASSERT_EQUALS(0, room.getRate());

    //test second ctor
    ASSERT_NO_THROW(EscapeRoomWrapper((char*)"room", 8));
    EscapeRoomWrapper room2((char*)"room", 8);
    ASSERT_EQUALS("room", room.getName());
    ASSERT_EQUALS(60, room2.getMaxTime());
    ASSERT_EQUALS(8, room2.level());
    ASSERT_EQUALS(6, room2.getMaxParticipants());
    ASSERT_EQUALS(0, room2.getRate());

}

void testWrapperCopyCtor(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    EscapeRoomWrapper copied_room = room;
    //test that all the values are equal
    ASSERT_EQUALS(room.getName(), copied_room.getName());
    ASSERT_EQUALS(room.getMaxTime(), copied_room.getMaxTime());
    ASSERT_EQUALS(room.level(), copied_room.level());
    ASSERT_EQUALS(room.getMaxParticipants(), copied_room.getMaxParticipants());
    ASSERT_EQUALS(room.getRate(), copied_room.getRate());

    //test that the rooms are diff
    room.rate(4);
    ASSERT_NOT_EQUAL(room.getRate(), copied_room.getRate());

}

void testWrapperAssignment(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    EscapeRoomWrapper assigned_room((char*)"test assignment", 5);
    assigned_room = room;
    //test that all the values have been updated
    ASSERT_EQUALS(room.getName(), assigned_room.getName());
    ASSERT_EQUALS(room.getMaxTime(), assigned_room.getMaxTime());
    ASSERT_EQUALS(room.level(), assigned_room.level());
    ASSERT_EQUALS(room.getMaxParticipants(), assigned_room.getMaxParticipants());
    ASSERT_EQUALS(room.getRate(), assigned_room.getRate());

    //test that the rooms are diff
    room.rate(4);
    ASSERT_NOT_EQUAL(room.getRate(), assigned_room.getRate());
}

void testWrapperOperatorEqual(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test same room
    ASSERT_TRUE(room == room);
    //test same values
    EscapeRoomWrapper room2((char*)"room", 50, 8, 12);
    ASSERT_TRUE(room == room2);
    //test diff values but same power calculation
    EscapeRoomWrapper room3((char*)"room", 25, 4, 3);
    ASSERT_TRUE(room == room3);
    //test diff name
    EscapeRoomWrapper room4((char*)"not room", 50, 8, 12);
    ASSERT_FALSE(room == room4);
    //test diff power calculation
    EscapeRoomWrapper room5((char*)"room", 49, 8, 12);
    ASSERT_FALSE(room == room5);

}

void testWrapperOperatorNotEqual(){

    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test same room
    ASSERT_FALSE(room != room);
    //test same values
    EscapeRoomWrapper room2((char*)"room", 50, 8, 12);
    ASSERT_FALSE(room != room2);
    //test diff values but same power calculation
    EscapeRoomWrapper room3((char*)"room", 25, 4, 3);
    ASSERT_FALSE(room != room3);
    //test diff name
    EscapeRoomWrapper room4((char*)"not room", 50, 8, 12);
    ASSERT_TRUE(room != room4);
    //test diff power calculation
    EscapeRoomWrapper room5((char*)"room", 49, 8, 12);
    ASSERT_TRUE(room != room5);
}

void testWrapperOperatorSmaller(){
    //test smaller power
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    EscapeRoomWrapper room2((char*)"room", 49, 8, 12);
    ASSERT_TRUE(room2 < room);
}

void testWrapperOperatorGreater(){
    //test greater power
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    EscapeRoomWrapper room2((char*)"room", 49, 8, 12);
    ASSERT_TRUE(room > room2);
}

void testWrapperPrint(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_PRINT("room (50/8/12)", room);
}

void testWrapperLevel(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_EQUALS(8, room.level());
}

void testWrapperRate(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test successful rate
    room.rate(1);
    ASSERT_EQUALS(1, room.getRate());
    //test success out of limits
    ASSERT_THROWS(EscapeRoomIllegalRateException ,room.rate(0));
    ASSERT_THROWS(EscapeRoomIllegalRateException, room.rate(6));
}

void testWrapperGetName(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_EQUALS("room", room.getName());
}

void testWrapperGetMaxTime(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_EQUALS(50, room.getMaxTime());
}

void testWrapperGetMaxParticipants(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_EQUALS(12, room.getMaxParticipants());

}

void testWrapperGetRate(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_EQUALS(0, room.getRate());
}

void testWrapperAddEnigma(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("enigma", EASY_ENIGMA, 2, elements);
    Enigma enigma2("enigma2", MEDIUM_ENIGMA);
    room.addEnigma(enigma);
    room.addEnigma(enigma2);
    //test that the enigmas are inserted to the end
    vector<Enigma>& vec = room.getAllEnigmas();
    ASSERT_TRUE(enigma2 == vec[1]);

    //test if a copy of the enigmas was inserted
    enigma.removeElement("book");
    vector<Enigma>& vec2 = room.getAllEnigmas();
    ASSERT_NO_THROW(vec2[0].removeElement("book"));
}

int main(){

    RUN_TEST(testWrapperCtor);
    RUN_TEST(testWrapperCopyCtor);
    RUN_TEST(testWrapperAssignment);
    RUN_TEST(testWrapperOperatorEqual);
    RUN_TEST(testWrapperOperatorNotEqual);
    RUN_TEST(testWrapperOperatorSmaller);
    RUN_TEST(testWrapperOperatorGreater);
    RUN_TEST(testWrapperPrint);
    RUN_TEST(testWrapperLevel);
    RUN_TEST(testWrapperRate);
    RUN_TEST(testWrapperGetName);
    RUN_TEST(testWrapperGetMaxTime);
    RUN_TEST(testWrapperGetMaxParticipants);
    RUN_TEST(testWrapperGetRate);
    RUN_TEST(testWrapperAddEnigma);

    return 0;
}
