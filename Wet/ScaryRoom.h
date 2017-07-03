//
// Created by Shahak on 02/07/2017.
//

#ifndef HW4_SCARYROOM_H
#define HW4_SCARYROOM_H

#include "EscapeRoomWrapper.h"


namespace mtm {
    namespace escaperoom {

        class ScaryRoom : public EscapeRoomWrapper {

        private:

            int ageLimit;
            int numOfScaryEnigmas;

            /**
             * a print function relevant for ScaryRoom that overrides the
             * virtual printing function of EscapeRoomWrapper
             */
            void print(std::ostream& output) const override;

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

            /**
             * sets a new minimum age limit for the specific scary room
             * @param limit - the new minimum age limit
             */
            void setNewAgeLimit(const int& limit);

            /**
             * increases the number of scary enigmas with the room by one
             */
            void incNumberOfScaryEnigmas();

            /**
             * find the minimum age limit of the room
             * @return - the minimum age limit of the specific scary room
             */
            int getAgeLimit() const;

            /**
             * a destructor for scary room to override the virtual base destructor
             */
            ~ScaryRoom() override = default;
        };
    }
}
#endif //HW4_SCARYROOM_H
