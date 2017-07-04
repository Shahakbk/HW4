//
// Created by Shahak on 03/07/2017.
//

#include <iostream>

#include "../EscapeRoomWrapper.h"
#include "../Company.h"
#include "../Exceptions.h"
#include "../mtmtest.h"

using namespace mtm::escaperoom;

void testCompanyCtor() {
    Company company("company", "052-123456");
}

void testCompanyCopyCtor() {
    Company company("company", "052-123456");
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);

    ScaryRoom scary_room((char*)"scary room", 50, 8, 12, 5, 2);
    Enigma enigma("enigma", EASY_ENIGMA);

    company.addEnigma(scary_room, enigma);
    company.addItem(scary_room, enigma, "book");

    Company copied_company = company;
    //test that all the values are the same


    //test that removing from the copied company doesn't effect the original one
    ASSERT_NO_THROW(copied_company.removeItem(scary_room, enigma, "book"));
    ASSERT_NO_THROW(copied_company.removeEnigma(scary_room, enigma));
    ASSERT_NO_THROW(copied_company.removeRoom(scary_room));
//    std::cout << "printintg" <<std::endl;

}
/*//TODO self assignment
void testCompanyAssignment() {
    Company company("company", "052-123456");
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);

    ScaryRoom scary_room((char*)"scary room", 50, 8, 12, 5, 2);
    Enigma enigma("enigma", EASY_ENIGMA);

    company.addEnigma(scary_room, enigma);
    company.addItem(scary_room, enigma, "book");

    Company assigned_company("assigned", "052");
    assigned_company.createRoom((char*)"room2", 40, 4, 10);
    assigned_company.createScaryRoom((char*)"scary room2", 40, 4, 40, 4, 3);
    assigned_company.createKidsRoom((char*)"kids room2", 40, 4, 40, 18);

    ScaryRoom scary_room2((char*)"scary room2", 40, 4, 40, 4, 3);
    Enigma enigma2("enigma2", EASY_ENIGMA);

    company.addEnigma(scary_room, enigma);
    company.addItem(scary_room, enigma, "map");

    assigned_company = company;
    //test all the values of the assigned company are the same as the original

    //test that removing from the assigned company doesn't effect the original one
    ASSERT_NO_THROW(assigned_company.removeItem(scary_room, enigma, "book"));
    ASSERT_NO_THROW(assigned_company.removeEnigma(scary_room, enigma));
    ASSERT_NO_THROW(assigned_company.removeRoom(scary_room));

    //test self assignment
}*/

void testCompanyCreateRoom() {
    Company company("company", "052-123456");
    company.createRoom((char*)"room", 50, 8, 12);
    //test if the room is in the company
    ASSERT_NO_THROW(set<EscapeRoomWrapper*>(company.getAllRooms()));
    set<EscapeRoomWrapper*> rooms = company.getAllRooms();
    ASSERT_EQUALS(1, rooms.size());
    set<EscapeRoomWrapper *>::iterator i = rooms.begin();
    EscapeRoomWrapper* room = *i;
    ASSERT_EQUALS("room", room->getName());
}

void testCompanyCreateScaryRoom() {
    Company company("company", "052-123456");
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    //test if the room is in the company
    ASSERT_NO_THROW(set<EscapeRoomWrapper*>(company.getAllRooms()));
    set<EscapeRoomWrapper*> rooms = company.getAllRooms();
    ASSERT_EQUALS(1, rooms.size());
    set<EscapeRoomWrapper *>::iterator i = rooms.begin();
    ScaryRoom* scary_room = dynamic_cast<ScaryRoom*>(*i);
    ASSERT_EQUALS("scary room", scary_room->getName());
    ASSERT_EQUALS(5, scary_room->getAgeLimit());
}

void testCompanyCreateKidsRoom() {
    Company company("company", "052-123456");
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    //test if the room is in the company
    ASSERT_NO_THROW(set<EscapeRoomWrapper*>(company.getAllRooms()));
    set<EscapeRoomWrapper*> rooms = company.getAllRooms();
    ASSERT_EQUALS(1, rooms.size());
    set<EscapeRoomWrapper *>::iterator i = rooms.begin();
    KidsRoom* kids_room = dynamic_cast<KidsRoom*>(*i);
    ASSERT_EQUALS("kids room", kids_room->getName());
    ASSERT_EQUALS(14, kids_room->getAgeLimit());
}

void testCompanyGetAllRooms() {
    Company company("company", "052-123456");
    //test company without rooms
    ASSERT_NO_THROW(set<EscapeRoomWrapper*>(company.getAllRooms()));
    set<EscapeRoomWrapper*> rooms = company.getAllRooms();
    ASSERT_EQUALS(0, rooms.size());

    //test company with diff types of rooms
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    ASSERT_NO_THROW(set<EscapeRoomWrapper*>(company.getAllRooms()));
    set<EscapeRoomWrapper*> rooms2 = company.getAllRooms();
    ASSERT_EQUALS(3, rooms2.size());

    set<EscapeRoomWrapper *>::iterator i = rooms2.begin();
    EscapeRoomWrapper* room = *i++;
    ASSERT_EQUALS("room", room->getName());
    ScaryRoom* scary_room = dynamic_cast<ScaryRoom*>(*i++);
    ASSERT_EQUALS("scary room", scary_room->getName());
    ASSERT_EQUALS(5, scary_room->getAgeLimit());
    KidsRoom* kids_room = dynamic_cast<KidsRoom*>(*i);
    ASSERT_EQUALS("kids room", kids_room->getName());
    ASSERT_EQUALS(14, kids_room->getAgeLimit());
}

void testCompanyRemoveRoom() {
    Company company("company", "052-123456");
    //test throw when company is empty
    EscapeRoomWrapper room((char*)"room", 50, 8, 12);
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeRoom(room));
    //test throw when the room is not in the company
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    EscapeRoomWrapper room2((char*)"not in company room", 50, 8, 12);
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeRoom(room2));

    //test successful removal
    ASSERT_NO_THROW(company.removeRoom(room));
    set<EscapeRoomWrapper*> rooms = company.getAllRooms();
    ASSERT_EQUALS(2, rooms.size());
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeRoom(room));

}

void testCompanyAddEnigma() {
    Company company("company", "052-123456");
    //test throw when company is empty
    ScaryRoom scaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    Enigma enigma("enigma", EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.addEnigma(scaryRoom, enigma));
    //test throw when room is not in the company
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    EscapeRoomWrapper room((char*)"not in company room", 50, 8, 12);
    ASSERT_THROWS(CompanyRoomNotFoundException, company.addEnigma(room,enigma));

    //test successful adding
    company.addEnigma(scaryRoom, enigma);
    ASSERT_NO_THROW(company.removeEnigma(scaryRoom, enigma));

}

void testCompanyRemoveEnigma() {
    Company company("company", "052-123456");
    //test throw when company is empty
    ScaryRoom scary_room((char*)"scary room", 50, 8, 12, 5, 2);
    Enigma enigma("enigma", EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.removeEnigma(scary_room, enigma));
    //test throw when room is not in the company
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    KidsRoom kids_room((char*)"kids room", 50, 8, 12, 14);
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.removeEnigma(kids_room, enigma));
    //test throw when room has no enigmas
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,
                  company.removeEnigma(kids_room, enigma));
    //test throw when room has enigmas but not the requested
    company.addEnigma(kids_room, enigma);
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, company.removeEnigma
            (kids_room, Enigma("enigma not in room", EASY_ENIGMA)));

    //test successful removal
    ASSERT_NO_THROW(company.removeEnigma(kids_room, enigma));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException, company.removeEnigma
            (kids_room, enigma));

}

void testCompanyAddItem() {
    Company company("company", "052-123456");
    //test throw when room is not in the company
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    KidsRoom kids_room((char*)"kids room", 50, 8, 12, 14);
    Enigma enigma("enigma", EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.addItem(kids_room, enigma, "book"));
    //test throw when the enigma is not in the room
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
                  company.addItem(kids_room, enigma, "book"));

    //test successful adding
    company.addEnigma(kids_room, enigma);
    ASSERT_NO_THROW(company.addItem(kids_room, enigma, "book"));
    ASSERT_NO_THROW(company.removeItem(kids_room, enigma, "book"));
}

void testCompanyRemoveItem() {
    Company company("company", "052-123456");
    //test throw when the room is not in the company
    company.createRoom((char*)"room", 50, 8, 12);
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    KidsRoom kids_room((char*)"kids room", 50, 8, 12, 14);
    Enigma enigma("enigma", EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.removeItem(kids_room, enigma, "book"));

    //test throw when enigma is not in the room
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
                  company.removeItem(kids_room, enigma, "book"));

    //test throw when the enigma doesn't have items
    company.addEnigma(kids_room, enigma);
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,
                  company.removeItem(kids_room, enigma, "book"));

    //test throw when the item is not in the enigma
    company.addItem(kids_room, enigma, "book");
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,
                  company.removeItem(kids_room, enigma, "map"));

    //test successful removal
    ASSERT_NO_THROW(company.removeItem(kids_room, enigma, "book"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,
                  company.removeItem(kids_room, enigma, "book"));
}

void testCompanyGetAllRoomsByType() {
    Company company("company", "052-123456");
    //test when there are no rooms in the company
    set<EscapeRoomWrapper*> rooms = company.getAllRoomsByType(SCARY_ROOM);
    ASSERT_EQUALS(0, rooms.size());

    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createScaryRoom((char*)"scary room2", 50, 8, 12, 5, 2);
    company.createScaryRoom((char*)"scary room3", 50, 8, 12, 5, 2);
    company.createRoom((char*)"room", 50, 8, 12);
    company.createRoom((char*)"room2", 50, 8, 12);
    company.createRoom((char*)"room3", 50, 8, 12);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    company.createKidsRoom((char*)"kids room2", 50, 8, 12, 14);
    company.createKidsRoom((char*)"kids room3", 50, 8, 12, 14);

    set<EscapeRoomWrapper*> rooms2 = company.getAllRoomsByType(KIDS_ROOM);
    ASSERT_EQUALS(3, rooms2.size());
    set<EscapeRoomWrapper*>::iterator i = rooms2.begin();
    KidsRoom* kids_room = dynamic_cast<KidsRoom*>(*i++);
    ASSERT_EQUALS("kids room", kids_room->getName());
    KidsRoom* kids_room2 = dynamic_cast<KidsRoom*>(*i++);
    ASSERT_EQUALS("kids room2", kids_room2->getName());
    KidsRoom* kids_room3 = dynamic_cast<KidsRoom*>(*i);
    ASSERT_EQUALS("kids room3", kids_room3->getName());

    //test that only base room types returns
    set<EscapeRoomWrapper*> rooms3 = company.getAllRoomsByType(BASE_ROOM);
    ASSERT_EQUALS(3, rooms3.size());
    set<EscapeRoomWrapper*>::iterator j = rooms3.begin();
    EscapeRoomWrapper* room = *j++;
    ASSERT_EQUALS("room", room->getName());
    EscapeRoomWrapper* room2 = *j++;
    ASSERT_EQUALS("room2", room2->getName());
    EscapeRoomWrapper* room3 = *j;
    ASSERT_EQUALS("room3", room3->getName());

}

void testCompanyGetRoomByName() {
    Company company("company", "052-123456");
    //test throw when company is empty
    ASSERT_THROWS(CompanyRoomNotFoundException, company.getRoomByName("room"));
    //test throw when there is no such room in the company
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createScaryRoom((char*)"scary room2", 50, 8, 12, 5, 2);
    company.createScaryRoom((char*)"scary room3", 50, 8, 12, 5, 2);
    company.createRoom((char*)"room", 50, 8, 12);
    company.createRoom((char*)"room2", 50, 8, 12);
    company.createRoom((char*)"room3", 50, 8, 12);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 8);
    company.createKidsRoom((char*)"kids room2", 50, 8, 12, 14);
    company.createKidsRoom((char*)"kids room3", 50, 8, 12, 14);

    ASSERT_THROWS(CompanyRoomNotFoundException, company.getRoomByName("room4"));

    //test successful return
    ASSERT_NO_THROW(company.getRoomByName("room"));
    KidsRoom* kids_room = dynamic_cast<KidsRoom*>(company.getRoomByName
            ("kids room"));

    ASSERT_EQUALS(8, kids_room->getAgeLimit());

}

void testCompanyPrint() {
    Company company("company", "052-123456");
    //test print when company is empty
    ASSERT_PRINT("company : 052-123456\n", company);

    //test company with rooms
    company.createScaryRoom((char*)"scary room", 50, 8, 12, 5, 2);
    company.createRoom((char*)"room", 50, 8, 12);
    company.createKidsRoom((char*)"kids room", 50, 8, 12, 14);
    ASSERT_PRINT("company : 052-123456\nScary Room: scary room (50/8/12/5)\n"
                 "Kids Room: kids room (50/8/12/14)\nroom (50/8/12)\n", company);
}

int main(){
    RUN_TEST(testCompanyCtor);
    RUN_TEST(testCompanyCopyCtor);
//    RUN_TEST(testCompanyAssignment);
    RUN_TEST(testCompanyCreateRoom);
    RUN_TEST(testCompanyCreateScaryRoom);
    RUN_TEST(testCompanyCreateKidsRoom);
    RUN_TEST(testCompanyGetAllRooms);
    RUN_TEST(testCompanyRemoveRoom);
    RUN_TEST(testCompanyAddEnigma);
    RUN_TEST(testCompanyRemoveEnigma);
    RUN_TEST(testCompanyAddItem);
    RUN_TEST(testCompanyRemoveItem);
    RUN_TEST(testCompanyGetAllRoomsByType);
    RUN_TEST(testCompanyGetRoomByName);
    RUN_TEST(testCompanyPrint);

    return 0;
}
