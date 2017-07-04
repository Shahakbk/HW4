//
// Created by adire on 28-Jun-17.
//

#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;

const int deafult_time = 60;
const int deafult_max_participants = 6;


EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime,
                                     const int &level,
                                     const int &maxParticipants) :
        escape_room(escapeRoomCreate(name, escapeTime, maxParticipants, level)){
    if (nullptr == escape_room) {
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &level) :
        escape_room(escapeRoomCreate(name, deafult_time,
                                     deafult_max_participants, level)) {
    if (nullptr == escape_room) {
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper &room) :
        escape_room(escapeRoomCopy(room.escape_room)), enigmas(room.enigmas) {
    if (nullptr == escape_room) {
        throw EscapeRoomMemoryProblemException();
    }
}

void EscapeRoomWrapper::addEnigma(const Enigma &enigma) {
    enigmas.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma &enigma) {
    if (0 == enigmas.size()) {
        throw EscapeRoomNoEnigmasException();
    }

    for (vector<Enigma>::iterator i = enigmas.begin(); i != enigmas.end(); ++i){
        if (*i == enigma) {
            enigmas.erase(i);
            return;
        }
    }

    throw EscapeRoomEnigmaNotFoundException();
}

Enigma EscapeRoomWrapper::getHardestEnigma() {
    if (0 == enigmas.size()) {
        throw EscapeRoomNoEnigmasException();
    }

    Enigma max_enigma = *enigmas.begin();
    for (vector<Enigma>::iterator i = enigmas.begin(); i != enigmas.end(); ++i){
        if (*i > max_enigma) {
            max_enigma = *i;
        }
    }

    return max_enigma;
}

vector<Enigma>& EscapeRoomWrapper::getAllEnigmas() {
    return enigmas;
}

void EscapeRoomWrapper::addElement(const Enigma& enigma, const string& element){

    for (vector<Enigma>::iterator i = enigmas.begin(); i != enigmas.end(); ++i){

        if (*i == enigma) {
            (*i).addElement(element);
            return;;
        }
    }

    throw EscapeRoomEnigmaNotFoundException();
}

void EscapeRoomWrapper::removeElement(const Enigma &enigma,
                                      const string& element) {

    for (vector<Enigma>::iterator i = enigmas.begin(); i != enigmas.end(); ++i){

        if (*i == enigma) {
            try {
                (*i).removeElement(element);
            } catch (EnigmaNoElementsException) {
                throw EnigmaNoElementsException();
            } catch (EnigmaElementNotFoundException) {
                throw EnigmaElementNotFoundException();
            }
            return;
        }
    }

    throw EscapeRoomEnigmaNotFoundException();
}

EscapeRoomWrapper &EscapeRoomWrapper::operator=(const EscapeRoomWrapper &room) {
    if (this == &room){
        return *this;
    }
    escape_room = escapeRoomCopy(room.escape_room);
    enigmas = room.enigmas;
    return *this;
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper &room) const {
    return areEqualRooms(escape_room, room.escape_room);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper &room) const {
    return !areEqualRooms(escape_room, room.escape_room);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper &room) const {
    return !isBiggerRoom(escape_room, room.escape_room);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper &room) const {
    return isBiggerRoom(escape_room, room.escape_room);
}

int EscapeRoomWrapper::level() const {
    return getLevel(escape_room);
}

void EscapeRoomWrapper::rate(const int &newRate) {
    if (newRate < 1 || newRate >5) {
        throw EscapeRoomIllegalRateException();
    }
    updateRate(escape_room, newRate);
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
    escapeRoomDestroy(escape_room);
}

std::string EscapeRoomWrapper::getName() const {
    char* tmp = roomGetName(escape_room);
    string name = tmp;
    free(tmp);
    return name;
}

double EscapeRoomWrapper::getRate() const {
    return roomGetRate(escape_room);
}

int EscapeRoomWrapper::getMaxTime() const {
    return roomGetMaxTime(escape_room);
}

int EscapeRoomWrapper::getMaxParticipants() const {
    return roomGetMaxParticipants(escape_room);
}

void EscapeRoomWrapper::print(std::ostream& output) const {
    output << this->getName() << " (" << this->getMaxTime() << "/" <<
           this->level() << "/" << this->getMaxParticipants() << ")";
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const EscapeRoomWrapper& room){
    room.print(output);
    return output;
}