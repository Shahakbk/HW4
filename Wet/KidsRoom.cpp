//
// Created by Shahak on 02/07/2017.
//

#include "KidsRoom.h"
#include "Exceptions.h"

using namespace mtm::escaperoom;
using std::string;

KidsRoom::KidsRoom(char* name, const int& escapeTime, const int& level,
         const int& maxParticipants, const int& ageLimit) :
        EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
        ageLimit(ageLimit) {}

void KidsRoom::setNewAgeLimit(const int& limit) {
    if (limit < 0) {
        throw KidsRoomIllegalAgeLimit();
    }
    ageLimit = limit;
}

int KidsRoom::getAgeLimit() const {
    return ageLimit;
}

/*KidsRoom::~KidsRoom() {
    delete(&ageLimit);
}*/

void KidsRoom::print(std::ostream &output) const {
    output << this->getName() << " (" << this->getMaxTime() << " /" <<
           this->level() << " /" << this->getMaxParticipants() << " /" <<
           this->getAgeLimit() << ")";
}