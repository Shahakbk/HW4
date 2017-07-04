//
// Created by Shahak on 02/07/2017.
//

#include "../KidsRoom.h"
#include "../Exceptions.h"
#include "../mtmtest.h"

using namespace mtm::escaperoom;

void testKidsRoomCtor(){
    ASSERT_NO_THROW(KidsRoom((char*)"room", 50, 8, 12, 14));
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS("room", kids_room.getName());
    ASSERT_EQUALS(50, kids_room.getMaxTime());
    ASSERT_EQUALS(8, kids_room.level());
    ASSERT_EQUALS(12, kids_room.getMaxParticipants());
    ASSERT_EQUALS(0, kids_room.getRate());
    ASSERT_EQUALS(14, kids_room.getAgeLimit());

}

void testKidsRoomCopyCtor(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    kids_room.addEnigma(Enigma("enigma", HARD_ENIGMA));
    kids_room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    kids_room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    KidsRoom copied_room = kids_room;
    //test that all the values are equal
    ASSERT_EQUALS(kids_room.getName(), copied_room.getName());
    ASSERT_EQUALS(kids_room.getMaxTime(), copied_room.getMaxTime());
    ASSERT_EQUALS(kids_room.level(), copied_room.level());
    ASSERT_EQUALS(kids_room.getMaxParticipants(), copied_room.getMaxParticipants());
    ASSERT_EQUALS(kids_room.getRate(), copied_room.getRate());
    ASSERT_EQUALS(kids_room.getAgeLimit(), copied_room.getAgeLimit());
    //test that the enigmas vector was copied successfully
    vector<Enigma>& copied_vec = copied_room.getAllEnigmas();
    ASSERT_EQUALS("enigma", copied_vec[0].getName());
    ASSERT_EQUALS(HARD_ENIGMA, copied_vec[0].getDifficulty());
    ASSERT_EQUALS("enigma2", copied_vec[1].getName());
    ASSERT_EQUALS(EASY_ENIGMA, copied_vec[1].getDifficulty());
    ASSERT_EQUALS("enigma3", copied_vec[2].getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, copied_vec[2].getDifficulty());

    //test that the rooms are diff
    kids_room.rate(4);
    ASSERT_NOT_EQUAL(kids_room.getRate(), copied_room.getRate());

}

void testKidsRoomAssignment(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    kids_room.addEnigma(Enigma("enigma", HARD_ENIGMA));
    kids_room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    kids_room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    KidsRoom assigned_room((char*)"test assignment", 40, 10, 7, 18);
    assigned_room = kids_room;
    //test that all the values have been updated
    ASSERT_EQUALS(kids_room.getName(), assigned_room.getName());
    ASSERT_EQUALS(kids_room.getMaxTime(), assigned_room.getMaxTime());
    ASSERT_EQUALS(kids_room.level(), assigned_room.level());
    ASSERT_EQUALS(kids_room.getMaxParticipants(),
                  assigned_room.getMaxParticipants());
    ASSERT_EQUALS(kids_room.getRate(), assigned_room.getRate());
    ASSERT_EQUALS(kids_room.getAgeLimit(), assigned_room.getAgeLimit());
    //test that the enigmas vector was assigned successfully
    vector<Enigma>& assigned_vec = assigned_room.getAllEnigmas();
    ASSERT_EQUALS("enigma", assigned_vec[0].getName());
    ASSERT_EQUALS(HARD_ENIGMA, assigned_vec[0].getDifficulty());
    ASSERT_EQUALS("enigma2", assigned_vec[1].getName());
    ASSERT_EQUALS(EASY_ENIGMA, assigned_vec[1].getDifficulty());
    ASSERT_EQUALS("enigma3", assigned_vec[2].getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, assigned_vec[2].getDifficulty());

    //test that the rooms are diff
    kids_room.rate(4);
    ASSERT_NOT_EQUAL(kids_room.getRate(), assigned_room.getRate());

    //test self assignment
    ASSERT_NO_THROW(kids_room = kids_room);
}

void testKidsRoomOperatorEqual(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test same room
    ASSERT_TRUE(kids_room == kids_room);
    //test same values
    KidsRoom kids_room2((char*)"room", 50, 8, 12, 14);
    ASSERT_TRUE(kids_room == kids_room2);
    //test diff values but same power calculation
    KidsRoom kids_room3((char*)"room", 25, 4, 3, 12);
    ASSERT_TRUE(kids_room == kids_room3);
    //test diff name
    KidsRoom kids_room4((char*)"not room", 50, 8, 12, 5);
    ASSERT_FALSE(kids_room == kids_room4);
    //test diff power calculation
    KidsRoom kids_room5((char*)"room", 49, 8, 12, 10);
    ASSERT_FALSE(kids_room == kids_room5);

}

void testKidsRoomOperatorNotEqual(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test same room
    ASSERT_FALSE(kids_room != kids_room);
    //test same values
    KidsRoom kids_room2((char*)"room", 50, 8, 12, 14);
    ASSERT_FALSE(kids_room != kids_room2);
    //test diff values but same power calculation
    KidsRoom kids_room3((char*)"room", 25, 4, 3, 12);
    ASSERT_FALSE(kids_room != kids_room3);
    //test diff name
    KidsRoom kids_room4((char*)"not room", 50, 8, 12, 5);
    ASSERT_TRUE(kids_room != kids_room4);
    //test diff power calculation
    KidsRoom kids_room5((char*)"room", 49, 8, 12, 10);
    ASSERT_TRUE(kids_room != kids_room5);
}

void testKidsRoomOperatorSmaller(){
    //test smaller power
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    KidsRoom kids_room2((char*)"room", 49, 8, 12, 14);
    ASSERT_TRUE(kids_room2 < kids_room);
}

void testKidsRoomOperatorGreater(){
    //test greater power
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    KidsRoom kids_room2((char*)"room", 49, 8, 12, 14);
    ASSERT_TRUE(kids_room > kids_room2);
}

void testKidsRoomPrint(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_PRINT("Kids Room: room (50/8/12/14)", kids_room);
}

void testKidsRoomLevel(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS(8, kids_room.level());
}

void testKidsRoomRate(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test successful rate
    kids_room.rate(1);
    ASSERT_EQUALS(1, kids_room.getRate());
    //test throw out of limits
    ASSERT_THROWS(EscapeRoomIllegalRateException ,kids_room.rate(0));
    ASSERT_THROWS(EscapeRoomIllegalRateException, kids_room.rate(6));
}

void testKidsRoomGetName(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS("room", kids_room.getName());
}

void testKidsRoomGetMaxTime(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS(50, kids_room.getMaxTime());
}

void testKidsRoomGetMaxParticipants(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS(12, kids_room.getMaxParticipants());

}

void testKidsRoomGetRate(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS(0, kids_room.getRate());
}

void testKidsRoomAddEnigma(){
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("enigma", EASY_ENIGMA, 2, elements);
    Enigma enigma2("enigma2", MEDIUM_ENIGMA);
    kids_room.addEnigma(enigma);
    kids_room.addEnigma(enigma2);
    //test that the enigmas are inserted to the end
    vector<Enigma>& vec = kids_room.getAllEnigmas();
    ASSERT_TRUE(enigma2 == vec[1]);

    //test if a copy of the enigmas was inserted
    enigma.removeElement("book");
    ASSERT_NO_THROW(kids_room.getAllEnigmas()[0].removeElement("book"));
}

void testKidsRoomRemoveEnigma() {
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test throw when room has no enigmas
    ASSERT_THROWS(EscapeRoomNoEnigmasException,
                  kids_room.removeEnigma(Enigma("enigma", EASY_ENIGMA)));
    //test throw when room has enigmas but not the requested one
    Enigma enigma("enigma", HARD_ENIGMA);
    kids_room.addEnigma(enigma);
    kids_room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    kids_room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    kids_room.addEnigma(Enigma("enigma4", MEDIUM_ENIGMA));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  kids_room.removeEnigma(Enigma("not in room", EASY_ENIGMA)));
    //test successful removal
    ASSERT_NO_THROW(kids_room.removeEnigma(enigma));
    //test that the enigma is no longer in the room
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  kids_room.removeEnigma(enigma));
    //test that the enigma is not deleted outside the room
    ASSERT_EQUALS(HARD_ENIGMA, enigma.getDifficulty());

}

void testKidsRoomGetHardestEnigma() {
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test throw when room has no enigmas
    ASSERT_THROWS(EscapeRoomNoEnigmasException, kids_room.getHardestEnigma());
    //test when there's only one enigma
    kids_room.addEnigma(Enigma("easy enigma", EASY_ENIGMA));
    ASSERT_NO_THROW(kids_room.getHardestEnigma());
    ASSERT_EQUALS("easy enigma", kids_room.getHardestEnigma().getName());
    ASSERT_EQUALS(EASY_ENIGMA, kids_room.getHardestEnigma().getDifficulty());

    //test when there are multiple enigmas
    kids_room.addEnigma(Enigma("medium enigma", MEDIUM_ENIGMA));
    ASSERT_EQUALS("medium enigma", kids_room.getHardestEnigma().getName());

    //test if the first enigma in the vector returns when equally complex
    Enigma enigma("hard enigma first", HARD_ENIGMA);
    enigma.addElement("book");
    kids_room.addEnigma(enigma);
    kids_room.addEnigma(Enigma("hard enigma second", HARD_ENIGMA));
    kids_room.addEnigma(Enigma("hard enigma third", HARD_ENIGMA));
    ASSERT_EQUALS("hard enigma first", kids_room.getHardestEnigma().getName());

    //test if the enigma stays in the room after returned
    kids_room.getHardestEnigma().removeElement("book");
    ASSERT_NO_THROW(kids_room.getHardestEnigma().removeElement("book"));
}

void testKidsRoomGetAllEnigmas() {
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test returned vector when no enigmas in the room
    vector<Enigma>& empty_vec = kids_room.getAllEnigmas();
    ASSERT_EQUALS(0, empty_vec.size());
    //test returned vector when there are some enigmas
    Enigma enigma("enigma", HARD_ENIGMA);
    enigma.addElement("book");
    kids_room.addEnigma(enigma);
    kids_room.addEnigma(Enigma("enigma2", HARD_ENIGMA));
    kids_room.addEnigma(Enigma("enigma3", HARD_ENIGMA));
    kids_room.addEnigma(Enigma("enigma4", MEDIUM_ENIGMA));
    kids_room.addEnigma(Enigma("enigma5", EASY_ENIGMA));
    vector<Enigma>& vec = kids_room.getAllEnigmas();
    ASSERT_EQUALS(5, vec.size());
    ASSERT_EQUALS("enigma", vec[0].getName());
    ASSERT_EQUALS("enigma5", vec[4].getName());

    //test that the returned vector doesn't effect the enigmas in the room
    kids_room.getAllEnigmas()[0].removeElement("book");
    ASSERT_NO_THROW(enigma.removeElement("book"));
}

void testKidsRoomSetNewAgeLimit() {
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    //test throw when age limit is not valid
    ASSERT_THROWS(KidsRoomIllegalAgeLimit, kids_room.setNewAgeLimit(-1));
    //test successful age limit set
    ASSERT_NO_THROW(kids_room.setNewAgeLimit(0));
    ASSERT_EQUALS(0, kids_room.getAgeLimit());
}

void testKidsRoomGetAgeLimit() {
    KidsRoom kids_room((char*)"room", 50, 8, 12, 14);
    ASSERT_EQUALS(14, kids_room.getAgeLimit());
}

int main() {

    RUN_TEST(testKidsRoomCtor);
    RUN_TEST(testKidsRoomCopyCtor);
    RUN_TEST(testKidsRoomAssignment);
    RUN_TEST(testKidsRoomOperatorEqual);
    RUN_TEST(testKidsRoomOperatorNotEqual);
    RUN_TEST(testKidsRoomOperatorSmaller);
    RUN_TEST(testKidsRoomOperatorGreater);
    RUN_TEST(testKidsRoomPrint);
    RUN_TEST(testKidsRoomLevel);
    RUN_TEST(testKidsRoomRate);
    RUN_TEST(testKidsRoomGetName);
    RUN_TEST(testKidsRoomGetMaxTime);
    RUN_TEST(testKidsRoomGetMaxParticipants);
    RUN_TEST(testKidsRoomGetRate);
    RUN_TEST(testKidsRoomAddEnigma);
    RUN_TEST(testKidsRoomRemoveEnigma);
    RUN_TEST(testKidsRoomGetHardestEnigma);
    RUN_TEST(testKidsRoomGetAllEnigmas);
    //added especially for kids room
    RUN_TEST(testKidsRoomSetNewAgeLimit);
    RUN_TEST(testKidsRoomGetAgeLimit);

    return 0;
}
