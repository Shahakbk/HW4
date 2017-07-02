//
// Created by Shahak on 02/07/2017.
//

#ifndef HW4_SCARYROOM_H
#define HW4_SCARYROOM_H

#include "EscapeRoomWrapper.h"


namespace mtm {
    namespace escaperoom {

        class ScaryRoom : public EscapeRoomWrapper {

        public:

            /**
             * receives all the params and creates a scary room
             * @param name - the name of the room
             * @param escapeTime - the maximum time to escape
             * @param level - the level of the room
             * @param maxParticipants - maximum of participants for the room
             * @param ageLimit - minimum age required for the room
             * @param numOfScaryEnigmas - number of scary enigmas in the room
             */
            ScaryRoom(char* name, const int& escapeTime, const int& level,
                      const int& maxParticipants, const int& ageLimit,
                      const int& numOfScaryEnigmas);

            void setNewAgeLimit(const int& limit);

            void incNumberOfScaryEnigmas();

            int getAgeLimit();

        private:

            int ageLimit;
            int numOfScaryEnigmas;


        };
    }
}
#endif //HW4_SCARYROOM_H
