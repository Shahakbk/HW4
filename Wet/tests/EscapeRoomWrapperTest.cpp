//
// Created by adire on 30-Jun-17.
//
#include "../EscapeRoomWrapper.h"
#include "../Exceptions.h"
#include "../mtmtest.h"

using namespace mtm::escaperoom;

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
    room.addEnigma(Enigma("enigma", HARD_ENIGMA));
    room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    EscapeRoomWrapper copied_room = room;
    //test that all the values are equal
    ASSERT_EQUALS(room.getName(), copied_room.getName());
    ASSERT_EQUALS(room.getMaxTime(), copied_room.getMaxTime());
    ASSERT_EQUALS(room.level(), copied_room.level());
    ASSERT_EQUALS(room.getMaxParticipants(), copied_room.getMaxParticipants());
    ASSERT_EQUALS(room.getRate(), copied_room.getRate());
    //test that the enigmas vector was copied successfully
    vector<Enigma>& copied_vec = copied_room.getAllEnigmas();
    ASSERT_EQUALS("enigma", copied_vec[0].getName());
    ASSERT_EQUALS(HARD_ENIGMA, copied_vec[0].getDifficulty());
    ASSERT_EQUALS("enigma2", copied_vec[1].getName());
    ASSERT_EQUALS(EASY_ENIGMA, copied_vec[1].getDifficulty());
    ASSERT_EQUALS("enigma3", copied_vec[2].getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, copied_vec[2].getDifficulty());

    //test that the rooms are diff
    room.rate(4);
    ASSERT_NOT_EQUAL(room.getRate(), copied_room.getRate());

}

void testWrapperAssignment(){
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    room.addEnigma(Enigma("enigma", HARD_ENIGMA));
    room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    EscapeRoomWrapper assigned_room((char*)"test assignment", 5);
    assigned_room = room;
    //test that all the values have been updated
    ASSERT_EQUALS(room.getName(), assigned_room.getName());
    ASSERT_EQUALS(room.getMaxTime(), assigned_room.getMaxTime());
    ASSERT_EQUALS(room.level(), assigned_room.level());
    ASSERT_EQUALS(room.getMaxParticipants(), assigned_room.getMaxParticipants());
    ASSERT_EQUALS(room.getRate(), assigned_room.getRate());
    //test that the enigmas vector was assigned successfully
    vector<Enigma>& assigned_vec = assigned_room.getAllEnigmas();
    ASSERT_EQUALS("enigma", assigned_vec[0].getName());
    ASSERT_EQUALS(HARD_ENIGMA, assigned_vec[0].getDifficulty());
    ASSERT_EQUALS("enigma2", assigned_vec[1].getName());
    ASSERT_EQUALS(EASY_ENIGMA, assigned_vec[1].getDifficulty());
    ASSERT_EQUALS("enigma3", assigned_vec[2].getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, assigned_vec[2].getDifficulty());

    //test that the rooms are diff
    room.rate(4);
    ASSERT_NOT_EQUAL(room.getRate(), assigned_room.getRate());

    //test self assignment
    ASSERT_NO_THROW(room = room);
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
    //test throw out of limits
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
    ASSERT_NO_THROW(room.getAllEnigmas()[0].removeElement("book"));
}

void testWrapperRemoveEnigma() {
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test throw when room has no enigmas
    ASSERT_THROWS(EscapeRoomNoEnigmasException,
                  room.removeEnigma(Enigma("enigma", EASY_ENIGMA)));
    //test throw when room has enigmas but not the requested one
    Enigma enigma("enigma", HARD_ENIGMA);
    room.addEnigma(enigma);
    room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    room.addEnigma(Enigma("enigma4", MEDIUM_ENIGMA));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  room.removeEnigma(Enigma("not in room", EASY_ENIGMA)));
    //test successful removal
    ASSERT_NO_THROW(room.removeEnigma(enigma));
    //test that the enigma is no longer in the room
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room.removeEnigma(enigma));
    //test that the enigma is not deleted outside the room
    ASSERT_EQUALS(HARD_ENIGMA, enigma.getDifficulty());

}

void testWrapperGetHardestEnigma() {
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test throw when room has no enigmas
    ASSERT_THROWS(EscapeRoomNoEnigmasException, room.getHardestEnigma());
    //test when there's only one enigma
    room.addEnigma(Enigma("easy enigma", EASY_ENIGMA));
    ASSERT_NO_THROW(room.getHardestEnigma());
    ASSERT_EQUALS("easy enigma", room.getHardestEnigma().getName());
    ASSERT_EQUALS(EASY_ENIGMA, room.getHardestEnigma().getDifficulty());

    //test when there are multiple enigmas
    room.addEnigma(Enigma("medium enigma", MEDIUM_ENIGMA));
    ASSERT_EQUALS("medium enigma", room.getHardestEnigma().getName());

    //test if the first enigma in the vector returns when equally complex
    Enigma enigma("hard enigma first", HARD_ENIGMA);
    enigma.addElement("book");
    room.addEnigma(enigma);
    room.addEnigma(Enigma("hard enigma second", HARD_ENIGMA));
    room.addEnigma(Enigma("hard enigma third", HARD_ENIGMA));
    ASSERT_EQUALS("hard enigma first", room.getHardestEnigma().getName());

    //test if the enigma stays in the room after returned
    room.getHardestEnigma().removeElement("book");
    ASSERT_NO_THROW(room.getHardestEnigma().removeElement("book"));
}

void testWrapperGetAllEnigmas() {
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test returned vector when no enigmas in the room
    vector<Enigma>& empty_vec = room.getAllEnigmas();
    ASSERT_EQUALS(0, empty_vec.size());
    //test returned vector when there are some enigmas
    Enigma enigma("enigma", HARD_ENIGMA);
    enigma.addElement("book");
    room.addEnigma(enigma);
    room.addEnigma(Enigma("enigma2", HARD_ENIGMA));
    room.addEnigma(Enigma("enigma3", HARD_ENIGMA));
    room.addEnigma(Enigma("enigma4", MEDIUM_ENIGMA));
    room.addEnigma(Enigma("enigma5", EASY_ENIGMA));
    vector<Enigma>& vec = room.getAllEnigmas();
    ASSERT_EQUALS(5, vec.size());
    ASSERT_EQUALS("enigma", vec[0].getName());
    ASSERT_EQUALS("enigma5", vec[4].getName());

    //test that the returned vector doesn't effect the enigmas in the room
    room.getAllEnigmas()[0].removeElement("book");
    ASSERT_NO_THROW(enigma.removeElement("book"));
}

void testWrapperAddElement() {
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test throw when the enigma is not in the room
    Enigma enigma("enigma", HARD_ENIGMA);
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  room.addElement(enigma, "book"));
    //test successful add
    room.addEnigma(enigma);
    ASSERT_NO_THROW(room.addElement(enigma, "book"));
    ASSERT_NO_THROW(room.getHardestEnigma().removeElement("book"));
}

void testWrapperRemoveElement() {
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    //test throw when the enigma is not in the room
    Enigma enigma("enigma", HARD_ENIGMA);
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  room.removeElement(enigma, "book"));
    //test throw when the enigma doesn't have elements
    room.addEnigma(enigma);
    ASSERT_THROWS(EnigmaNoElementsException,
                  room.removeElement(enigma, "book"));
    //test throw when the enigma doesn't have the specific element
    room.addElement(enigma, "map");
    room.addElement(enigma, "lamp");
    ASSERT_THROWS(EnigmaElementNotFoundException,
                  room.removeElement(enigma, "book"));
    //test successful removal
    ASSERT_NO_THROW(room.removeElement(enigma, "lamp"));
    ASSERT_THROWS(EnigmaElementNotFoundException,
                  room.removeElement(enigma, "lamp"));
}

int main() {

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
    RUN_TEST(testWrapperRemoveEnigma);
    RUN_TEST(testWrapperGetHardestEnigma);
    RUN_TEST(testWrapperGetAllEnigmas);
    RUN_TEST(testWrapperAddElement);
    RUN_TEST(testWrapperRemoveElement);

    return 0;
}
