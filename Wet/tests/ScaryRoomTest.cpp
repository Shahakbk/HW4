//
// Created by Shahak on 02/07/2017.
//

#include <iostream>

#include "../ScaryRoom.h"
#include "../Exceptions.h"
#include "../mtmtest.h"

using namespace mtm::escaperoom;
using std::cout;
using std::endl;

void testScaryRoomCtor(){
    ASSERT_NO_THROW(ScaryRoom((char*)"room", 50, 8, 12, 5, 2));
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS("room", scary_room.getName());
    ASSERT_EQUALS(50, scary_room.getMaxTime());
    ASSERT_EQUALS(8, scary_room.level());
    ASSERT_EQUALS(12, scary_room.getMaxParticipants());
    ASSERT_EQUALS(0, scary_room.getRate());
    ASSERT_EQUALS(5, scary_room.getAgeLimit());

}

void testScaryRoomCopyCtor(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    scary_room.addEnigma(Enigma("enigma", HARD_ENIGMA));
    scary_room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    scary_room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    ScaryRoom copied_room = scary_room;
    //test that all the values are equal
    ASSERT_EQUALS(scary_room.getName(), copied_room.getName());
    ASSERT_EQUALS(scary_room.getMaxTime(), copied_room.getMaxTime());
    ASSERT_EQUALS(scary_room.level(), copied_room.level());
    ASSERT_EQUALS(scary_room.getMaxParticipants(), copied_room.getMaxParticipants());
    ASSERT_EQUALS(scary_room.getRate(), copied_room.getRate());
    ASSERT_EQUALS(scary_room.getAgeLimit(), copied_room.getAgeLimit());
    //test that the enigmas vector was copied successfully
    vector<Enigma>& copied_vec = copied_room.getAllEnigmas();
    ASSERT_EQUALS("enigma", copied_vec[0].getName());
    ASSERT_EQUALS(HARD_ENIGMA, copied_vec[0].getDifficulty());
    ASSERT_EQUALS("enigma2", copied_vec[1].getName());
    ASSERT_EQUALS(EASY_ENIGMA, copied_vec[1].getDifficulty());
    ASSERT_EQUALS("enigma3", copied_vec[2].getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, copied_vec[2].getDifficulty());

    //test that the rooms are diff
    scary_room.rate(4);
    ASSERT_NOT_EQUAL(scary_room.getRate(), copied_room.getRate());

}

void testScaryRoomAssignment(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    scary_room.addEnigma(Enigma("enigma", HARD_ENIGMA));
    scary_room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    scary_room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    ScaryRoom assigned_room((char*)"test assignment", 40, 10, 7, 3, 4);
    assigned_room = scary_room;
    //test that all the values have been updated
    ASSERT_EQUALS(scary_room.getName(), assigned_room.getName());
    ASSERT_EQUALS(scary_room.getMaxTime(), assigned_room.getMaxTime());
    ASSERT_EQUALS(scary_room.level(), assigned_room.level());
    ASSERT_EQUALS(scary_room.getMaxParticipants(),
                  assigned_room.getMaxParticipants());
    ASSERT_EQUALS(scary_room.getRate(), assigned_room.getRate());
    ASSERT_EQUALS(scary_room.getAgeLimit(), assigned_room.getAgeLimit());
    //test that the enigmas vector was assigned successfully
    vector<Enigma>& assigned_vec = assigned_room.getAllEnigmas();
    ASSERT_EQUALS("enigma", assigned_vec[0].getName());
    ASSERT_EQUALS(HARD_ENIGMA, assigned_vec[0].getDifficulty());
    ASSERT_EQUALS("enigma2", assigned_vec[1].getName());
    ASSERT_EQUALS(EASY_ENIGMA, assigned_vec[1].getDifficulty());
    ASSERT_EQUALS("enigma3", assigned_vec[2].getName());
    ASSERT_EQUALS(MEDIUM_ENIGMA, assigned_vec[2].getDifficulty());

    //test that the rooms are diff
    scary_room.rate(4);
    ASSERT_NOT_EQUAL(scary_room.getRate(), assigned_room.getRate());

    //test self assignment
    ASSERT_NO_THROW(scary_room = scary_room);
}

void testScaryRoomOperatorEqual(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test same room
    ASSERT_TRUE(scary_room == scary_room);
    //test same values
    ScaryRoom scary_room2((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_TRUE(scary_room == scary_room2);
    //test diff values but same power calculation
    ScaryRoom scary_room3((char*)"room", 25, 4, 3, 3, 4);
    ASSERT_TRUE(scary_room == scary_room3);
    //test diff name
    ScaryRoom scary_room4((char*)"not room", 50, 8, 12, 2, 1);
    ASSERT_FALSE(scary_room == scary_room4);
    //test diff power calculation
    ScaryRoom scary_room5((char*)"room", 49, 8, 12, 10, 5);
    ASSERT_FALSE(scary_room == scary_room5);

}

void testScaryRoomOperatorNotEqual(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test same room
    ASSERT_FALSE(scary_room != scary_room);
    //test same values
    ScaryRoom scary_room2((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_FALSE(scary_room != scary_room2);
    //test diff values but same power calculation
    ScaryRoom scary_room3((char*)"room", 25, 4, 3, 3, 4);
    ASSERT_FALSE(scary_room != scary_room3);
    //test diff name
    ScaryRoom scary_room4((char*)"not room", 50, 8, 12, 2, 1);
    ASSERT_TRUE(scary_room != scary_room4);
    //test diff power calculation
    ScaryRoom scary_room5((char*)"room", 49, 8, 12, 10, 5);
    ASSERT_TRUE(scary_room != scary_room5);
}

void testScaryRoomOperatorSmaller(){
    //test smaller power
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ScaryRoom scary_room2((char*)"room", 49, 8, 12, 5, 2);
    ASSERT_TRUE(scary_room2 < scary_room);
}

void testScaryRoomOperatorGreater(){
    //test greater power
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ScaryRoom scary_room2((char*)"room", 49, 8, 12, 5, 2);
    ASSERT_TRUE(scary_room > scary_room2);
}

void testScaryRoomPrint(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_PRINT("Scary Room: room (50/8/12/5)", scary_room);
}

void testScaryRoomLevel(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS(8, scary_room.level());
}

void testScaryRoomRate(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test successful rate
    scary_room.rate(1);
    ASSERT_EQUALS(1, scary_room.getRate());
    //test throw out of limits
    ASSERT_THROWS(EscapeRoomIllegalRateException ,scary_room.rate(0));
    ASSERT_THROWS(EscapeRoomIllegalRateException, scary_room.rate(6));
}

void testScaryRoomGetName(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS("room", scary_room.getName());
}

void testScaryRoomGetMaxTime(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS(50, scary_room.getMaxTime());
}

void testScaryRoomGetMaxParticipants(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS(12, scary_room.getMaxParticipants());

}

void testScaryRoomGetRate(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS(0, scary_room.getRate());
}

void testScaryRoomAddEnigma(){
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    set<string> elements;
    elements.insert("book");
    elements.insert("clock");
    Enigma enigma("enigma", EASY_ENIGMA, 2, elements);
    Enigma enigma2("enigma2", MEDIUM_ENIGMA);
    scary_room.addEnigma(enigma);
    scary_room.addEnigma(enigma2);
    //test that the enigmas are inserted to the end
    vector<Enigma>& vec = scary_room.getAllEnigmas();
    ASSERT_TRUE(enigma2 == vec[1]);

    //test if a copy of the enigmas was inserted
    enigma.removeElement("book");
    ASSERT_NO_THROW(scary_room.getAllEnigmas()[0].removeElement("book"));
}

void testScaryRoomRemoveEnigma() {
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test throw when room has no enigmas
    ASSERT_THROWS(EscapeRoomNoEnigmasException,
                  scary_room.removeEnigma(Enigma("enigma", EASY_ENIGMA)));
    //test throw when room has enigmas but not the requested one
    Enigma enigma("enigma", HARD_ENIGMA);
    scary_room.addEnigma(enigma);
    scary_room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
    scary_room.addEnigma(Enigma("enigma3", MEDIUM_ENIGMA));
    scary_room.addEnigma(Enigma("enigma4", MEDIUM_ENIGMA));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  scary_room.removeEnigma(Enigma("not in room", EASY_ENIGMA)));
    //test successful removal
    ASSERT_NO_THROW(scary_room.removeEnigma(enigma));
    //test that the enigma is no longer in the room
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
                  scary_room.removeEnigma(enigma));
    //test that the enigma is not deleted outside the room
    ASSERT_EQUALS(HARD_ENIGMA, enigma.getDifficulty());

}

void testScaryRoomGetHardestEnigma() {
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test throw when room has no enigmas
    ASSERT_THROWS(EscapeRoomNoEnigmasException, scary_room.getHardestEnigma());
    //test when there's only one enigma
    scary_room.addEnigma(Enigma("easy enigma", EASY_ENIGMA));
    ASSERT_NO_THROW(scary_room.getHardestEnigma());
    ASSERT_EQUALS("easy enigma", scary_room.getHardestEnigma().getName());
    ASSERT_EQUALS(EASY_ENIGMA, scary_room.getHardestEnigma().getDifficulty());

    //test when there are multiple enigmas
    scary_room.addEnigma(Enigma("medium enigma", MEDIUM_ENIGMA));
    ASSERT_EQUALS("medium enigma", scary_room.getHardestEnigma().getName());

    //test if the first enigma in the vector returns when equally complex
    Enigma enigma("hard enigma first", HARD_ENIGMA);
    enigma.addElement("book");
    scary_room.addEnigma(enigma);
    scary_room.addEnigma(Enigma("hard enigma second", HARD_ENIGMA));
    scary_room.addEnigma(Enigma("hard enigma third", HARD_ENIGMA));
    ASSERT_EQUALS("hard enigma first", scary_room.getHardestEnigma().getName());

    //test if the enigma stays in the room after returned
    scary_room.getHardestEnigma().removeElement("book");
    ASSERT_NO_THROW(scary_room.getHardestEnigma().removeElement("book"));
}

void testScaryRoomGetAllEnigmas() {
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test returned vector when no enigmas in the room
    vector<Enigma>& empty_vec = scary_room.getAllEnigmas();
    ASSERT_EQUALS(0, empty_vec.size());
    //test returned vector when there are some enigmas
    Enigma enigma("enigma", HARD_ENIGMA);
    enigma.addElement("book");
    scary_room.addEnigma(enigma);
    scary_room.addEnigma(Enigma("enigma2", HARD_ENIGMA));
    scary_room.addEnigma(Enigma("enigma3", HARD_ENIGMA));
    scary_room.addEnigma(Enigma("enigma4", MEDIUM_ENIGMA));
    scary_room.addEnigma(Enigma("enigma5", EASY_ENIGMA));
    vector<Enigma>& vec = scary_room.getAllEnigmas();
    ASSERT_EQUALS(5, vec.size());
    ASSERT_EQUALS("enigma", vec[0].getName());
    ASSERT_EQUALS("enigma5", vec[4].getName());

    //test that the returned vector doesn't effect the enigmas in the room
    scary_room.getAllEnigmas()[0].removeElement("book");
    ASSERT_NO_THROW(enigma.removeElement("book"));
}

void testScaryRoomSetNewAgeLimit() {
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    //test throw when age limit is not valid
    ASSERT_THROWS(ScaryRoomIllegalAgeLimit ,scary_room.setNewAgeLimit(-1));
    //test successful age limit set
    ASSERT_NO_THROW(scary_room.setNewAgeLimit(0));
    ASSERT_EQUALS(0, scary_room.getAgeLimit());
}

void testScaryRoomIncNumberOfScaryEnigmas() {
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_NO_THROW(scary_room.incNumberOfScaryEnigmas());
}

void testScaryRoomGetAgeLimit() {
    ScaryRoom scary_room((char*)"room", 50, 8, 12, 5, 2);
    ASSERT_EQUALS(5, scary_room.getAgeLimit());
}

int main() {

    RUN_TEST(testScaryRoomCtor);
    RUN_TEST(testScaryRoomCopyCtor);
    RUN_TEST(testScaryRoomAssignment);
    RUN_TEST(testScaryRoomOperatorEqual);
    RUN_TEST(testScaryRoomOperatorNotEqual);
    RUN_TEST(testScaryRoomOperatorSmaller);
    RUN_TEST(testScaryRoomOperatorGreater);
    RUN_TEST(testScaryRoomPrint);
    RUN_TEST(testScaryRoomLevel);
    RUN_TEST(testScaryRoomRate);
    RUN_TEST(testScaryRoomGetName);
    RUN_TEST(testScaryRoomGetMaxTime);
    RUN_TEST(testScaryRoomGetMaxParticipants);
    RUN_TEST(testScaryRoomGetRate);
    RUN_TEST(testScaryRoomAddEnigma);
    RUN_TEST(testScaryRoomRemoveEnigma);
    RUN_TEST(testScaryRoomGetHardestEnigma);
    RUN_TEST(testScaryRoomGetAllEnigmas);
    //added especially for scary room
    RUN_TEST(testScaryRoomSetNewAgeLimit);
    RUN_TEST(testScaryRoomIncNumberOfScaryEnigmas);
    RUN_TEST(testScaryRoomGetAgeLimit);

    return 0;
}
