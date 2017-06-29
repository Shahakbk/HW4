//
// Created by adire on 28-Jun-17.
//

#include "EscapeRoomWrapper.h"

using namespace mtm::escaperoom;
using std::string;

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime,
                                     const int &level,
                                     const int &maxParticipants) {

    escape_room = escapeRoomCreate(name, escapeTime, level, maxParticipants);
}

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &level) {

    escape_room = escapeRoomCreate(name, 60, level, 0);
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper &room) {

    escape_room = escapeRoomCopy(room.escape_room);
}

EscapeRoomWrapper::~EscapeRoomWrapper() {

    escapeRoomDestroy(escape_room);
}