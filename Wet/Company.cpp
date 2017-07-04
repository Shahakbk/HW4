//
// Created by Shahak on 02/07/2017.
//

#include "Company.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;
using std::cout;
using std::endl;

Company::Company(string name, string phoneNumber) : name(name),
                                                    phoneNumber(phoneNumber) {}

Company::Company(const Company& company) : name(company.name),
                                           phoneNumber(company.phoneNumber){
    std::set<EscapeRoomWrapper*>::iterator i = company.rooms.begin();
    for ( ; i != company.rooms.end(); ++i) {
        EscapeRoomWrapper* room = (*i)->clone();
        rooms.insert(room);
    }
}

Company::~Company() {
    std::set<EscapeRoomWrapper*>::iterator to_remove = rooms.begin();

    while (to_remove != rooms.end()){
        delete(*to_remove);
        rooms.erase(to_remove);
        to_remove = rooms.begin();
    }
}

Company& Company::operator=(const Company& company) {
    if (this == &company){
        return *this;
    }
    name = company.name;
    phoneNumber = company.phoneNumber;

    std::set<EscapeRoomWrapper*>::iterator to_remove = rooms.begin();
    while (to_remove != rooms.end()){
        removeRoom(**to_remove);
        to_remove = rooms.begin();
    }

    std::set<EscapeRoomWrapper*>::iterator i = company.rooms.begin();
    for ( ; i != company.rooms.end(); ++i) {
        EscapeRoomWrapper* tmp = (*i)->clone();
        rooms.insert(tmp);
    }
    return *this;
}

void Company::createRoom(char *name, const int &escapeTime, const int &level,
                         const int &maxParticipants) {
    try {
        rooms.insert(new EscapeRoomWrapper(name, escapeTime, level,
                                           maxParticipants));
    } catch (EscapeRoomMemoryProblemException) {
        throw CompanyMemoryProblemException();
    }
}

void Company::createScaryRoom(char *name, const int &escapeTime,
                              const int &level, const int &maxParticipants,
                              const int &ageLimit,
                              const int &numOfScaryEnigmas) {
    try {
        rooms.insert(new ScaryRoom(name, escapeTime, level, maxParticipants,
                                   ageLimit, numOfScaryEnigmas));
    } catch (EscapeRoomMemoryProblemException) {
        throw CompanyMemoryProblemException();
    }
}

void Company::createKidsRoom(char *name, const int &escapeTime,
                             const int &level, const int &maxParticipants,
                             const int &ageLimit) {
    try {
        //TODO double check
        rooms.insert(new KidsRoom(name, escapeTime, level, maxParticipants,
                                  ageLimit));
    } catch (EscapeRoomMemoryProblemException) {
        throw CompanyMemoryProblemException();
    }
}

set<EscapeRoomWrapper *> Company::getAllRooms() const {
    return rooms;
}

void Company::removeRoom(const EscapeRoomWrapper &room) {

    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin();
         i != rooms.end(); ++i) {

        if (**i == room) {
            delete(*i);
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

    set<EscapeRoomWrapper*> newSet = set<EscapeRoomWrapper*>();
    //TODO make sure
    for (set<EscapeRoomWrapper *>::iterator i = rooms.begin(); i != rooms.end(); ++i) {

        if (type == KIDS_ROOM) {
            KidsRoom* ptrRoom = dynamic_cast<KidsRoom*>(*i);
                if (nullptr != ptrRoom) {
                //(*newSet).insert(*i);
                newSet.insert(*i);
                continue;
            }
        } else if (type == SCARY_ROOM) {
            ScaryRoom* ptrRoom = dynamic_cast<ScaryRoom*>(*i);
            if (nullptr != ptrRoom) {
                //(*newSet).insert(*i);
                newSet.insert(*i);
                continue;
            }
        }else if (type == BASE_ROOM) {
            ScaryRoom* ptrRoom = dynamic_cast<ScaryRoom*>(*i);
            KidsRoom* ptrRoom2 = dynamic_cast<KidsRoom*>(*i);
            if (nullptr == ptrRoom && nullptr == ptrRoom2) {
                newSet.insert(*i);
                continue;
            }
        }
    }
    return newSet;
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
    output << company.name << " : " << company.phoneNumber << endl;
    for (set<EscapeRoomWrapper *>::iterator i = company.rooms.begin();
         i != company.rooms.end(); ++i) {
        output << **i << endl;
    }
    return output;
}
