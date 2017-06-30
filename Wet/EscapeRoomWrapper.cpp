//
// Created by adire on 28-Jun-17.
//

#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime,
                                     const int &level,
                                     const int &maxParticipants) :
        escape_room(escapeRoomCreate(name, escapeTime, level, maxParticipants)){
    if (escape_room == NULL) {
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &level) :
        escape_room(escapeRoomCreate(name, 60, level, 6)) {
    if (escape_room == NULL) {
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper &room) :
        escape_room(escapeRoomCopy(room.escape_room)) {
    if (escape_room == NULL) {
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper &EscapeRoomWrapper::operator=(const EscapeRoomWrapper &room) {
    EscapeRoom tmp = escapeRoomCopy(room.escape_room);
    escapeRoomDestroy(escape_room);
    escape_room = tmp;
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
    if (newRate < 0 || newRate >5) {
        throw EscapeRoomIllegalRateException();
    }
    updateRate(escape_room, newRate);
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
    escapeRoomDestroy(escape_room);
}

std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room){
    return output << getName() << "(" << getMaxTime() << "/" << level() <<
                  "/" << getMaxParticipants() << ")";
}

std::string EscapeRoomWrapper::getName() const {
    return roomGetName(escape_room);
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