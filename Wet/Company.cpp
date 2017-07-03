//
// Created by Shahak on 02/07/2017.
//

#include "Company.h"
#include "ScaryRoom.h"
#include "KidsRoom.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;
using std::cout;
using std::endl;

Company::Company(string name, string phoneNumber) : name(name),
                                                    phoneNumber(phoneNumber) {}

Company::Company(const Company &company) :
        name(company.name),
        phoneNumber(company.phoneNumber),
        rooms(company.rooms) {}

Company::~Company() {
    delete(&name);
    delete(&phoneNumber);
    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin();
         i != rooms.end(); ++i) {
        delete(*i);
    }
    delete(&rooms);
}

Company &Company::operator=(const Company &company) {
    if (this == &company) {
        return *this;
    }

    delete (&rooms);
    rooms = company.rooms;
    //TODO double check^
    name = company.name;
    phoneNumber = company.phoneNumber;
    return *this;
}

void Company::createRoom(char *name, const int &escapeTime, const int &level,
                         const int &maxParticipants) {
    try {
        EscapeRoomWrapper newRoom = EscapeRoomWrapper(name, escapeTime, level,
                                                      maxParticipants);
        rooms.insert(&newRoom);
    } catch (EscapeRoomMemoryProblemException) {
        throw CompanyMemoryProblemException();
    }
}

void Company::createScaryRoom(char *name, const int &escapeTime,
                              const int &level, const int &maxParticipants,
                              const int &ageLimit,
                              const int &numOfScaryEnigmas) {
    try {
        ScaryRoom scaryRoom = ScaryRoom(name, escapeTime, level,
                                        maxParticipants, ageLimit,
                                        numOfScaryEnigmas);
        rooms.insert(&scaryRoom);
    } catch (EscapeRoomMemoryProblemException) {
        throw CompanyMemoryProblemException();
    }
}

void Company::createKidsRoom(char *name, const int &escapeTime,
                             const int &level, const int &maxParticipants,
                             const int &ageLimit) {
    try {
        KidsRoom kidsRoom = KidsRoom(name, escapeTime, level,
                                     maxParticipants, ageLimit);
        rooms.insert(&kidsRoom);
    } catch (EscapeRoomMemoryProblemException) {
        throw CompanyMemoryProblemException();
    }
}

set<EscapeRoomWrapper *> Company::getAllRooms() const {
    return rooms;
    //TODO - FAQ says there's no need to create a copy. change to const &?
}

void Company::removeRoom(const EscapeRoomWrapper &room) {

    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin();
         i != rooms.end(); ++i) {

        if (**i == room) {
            //TODO make sure enigmas are erased
            rooms.erase(i);
            return;
        }
    }

    throw CompanyRoomNotFoundException();
}

//TODO can we add or remove const??
void Company::addEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {

    for (set<EscapeRoomWrapper*>::iterator i = rooms.begin();
         i != rooms.end() ; ++i) {

        if (**i == room) {
            (*i)->addEnigma(enigma);
            return;
        }
    }

    throw CompanyRoomNotFoundException();
}

void Company::removeEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {

    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin();
         i != rooms.end(); ++i) {

        if (**i == room) {
            try {
                (*i)->removeEnigma(enigma);
            } catch (EscapeRoomNoEnigmasException) {
                throw CompanyRoomHasNoEnigmasException();
            } catch (EscapeRoomEnigmaNotFoundException) {
                throw CompanyRoomEnigmaNotFoundException();
            }

            return;;
        }
    }

    throw CompanyRoomNotFoundException();
}

void Company::addItem(const EscapeRoomWrapper& room, const Enigma& enigma,
                      const string& element) {

    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin();
         i != rooms.end(); ++i) {

        if (**i == room) {

            try {
                (*i)->addElement(enigma, element);
            } catch (EscapeRoomEnigmaNotFoundException) {
                throw CompanyRoomEnigmaNotFoundException();
            }

            return;
        }
    }

    throw CompanyRoomNotFoundException();
}

void Company::removeItem(const EscapeRoomWrapper& room,
                                   const Enigma& enigma, const string& element) {
    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin();
         i != rooms.end(); ++i) {

        if (**i == room) {

            try {
                (*i)->removeElement(enigma, element);
            } catch (EnigmaNoElementsException) {
                throw CompanyRoomEnigmaHasNoElementsException();
            } catch (EnigmaElementNotFoundException) {
                throw CompanyRoomEnigmaElementNotFoundException();
            } catch (EscapeRoomEnigmaNotFoundException) {
                throw CompanyRoomEnigmaNotFoundException();
            }
            return;
        }
    }

    throw CompanyRoomNotFoundException();
}

set<EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const {

    set<EscapeRoomWrapper*> *newSet = new set<EscapeRoomWrapper*>();
    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin(); i != rooms.end(); ++i) {

        if (type == KIDS_ROOM) {
            KidsRoom* ptrRoom = dynamic_cast<KidsRoom*>(*i);
            if (nullptr != ptrRoom) {
                (*newSet).insert(*i);
                continue;
            }
        }

        if (type == SCARY_ROOM) {
            ScaryRoom* ptrRoom = dynamic_cast<ScaryRoom*>(*i);
            if (nullptr != ptrRoom) {
                (*newSet).insert(*i);
                continue;
            }
        }

        // not using else because a type may be added (?)
        if (type == BASE_ROOM) {
            EscapeRoomWrapper* ptrRoom = dynamic_cast<EscapeRoomWrapper*>(*i);
            //TODO make sure this ^ doesn't take scary & kids as well
            if (nullptr != ptrRoom) {
                (*newSet).insert(*i);
                continue;
            }
        }
    }

    return *newSet;
}

EscapeRoomWrapper* Company::getRoomByName(const string& name) const {

    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin(); i != rooms.end(); ++i) {

        if ( (*i)->getName() == name ) {
            return *i;
        }
    }

    throw CompanyRoomNotFoundException();
}

bool mtm::escaperoom::operator==(const Company &a, const Company &b) {
    return (a.name == b.name && a.phoneNumber == b.phoneNumber
            && a.rooms == b.rooms);
    //TODO double check set comparison
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const Company& company) {
    cout << company.name << " : " << company.phoneNumber << endl;
    for (set<EscapeRoomWrapper *>::iterator i = company.getAllRooms().begin();
         i != company.getAllRooms().end(); ++i) {
        cout << *i << endl;
    }

    return output;
}
