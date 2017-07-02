//
// Created by Shahak on 02/07/2017.
//

#include "ScaryRoom.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;

ScaryRoom::ScaryRoom(char* name, const int& escapeTime, const int& level,
          const int& maxParticipants, const int& ageLimit,
          const int& numOfScaryEnigmas):
        EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
        ageLimit(ageLimit), numOfScaryEnigmas(numOfScaryEnigmas) {}

void ScaryRoom::setNewAgeLimit(const int& limit) {
    if (limit < 0) {
        throw ScaryRoomIllegalAgeLimit();
    }
    ageLimit = limit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
    numOfScaryEnigmas++;
}

int ScaryRoom::getAgeLimit() const {
    return ageLimit;
}

void ScaryRoom::print(std::ostream &output) const {
    output << this->getName() << " (" << this->getMaxTime() << " /" <<
           this->level() << " /" << this->getMaxParticipants() << " /" <<
           this->getAgeLimit() << ")";
}