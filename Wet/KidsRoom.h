//
// Created by Shahak on 02/07/2017.
//

#ifndef HW4_KIDSROOM_H
#define HW4_KIDSROOM_H

#include "EscapeRoomWrapper.h"


namespace mtm {
    namespace escaperoom {
        class KidsRoom : public EscapeRoomWrapper {

        private:

            int ageLimit;

            /**
             * a print function relevant for KidsRoom that overrides the
             * virtual printing function of EscapeRoomWrapper
             */
            void print(std::ostream &output) const;

        public:

            /**
             * receives all the parameters and build a kids room
             * @param name - the name of the room
             * @param escapeTime - the time to escape from the room
             * @param level - the room level
             * @param maxParticipants - the max number of participants
             * @param ageLimit - the maximum age accepted
             */
            KidsRoom(char* name, const int& escapeTime, const int& level,
                     const int& maxParticipants, const int& ageLimit);

            /**
             * sets a new maximum age limit for the specific kids room
             * @param limit - the new maximum age limit
             */
            void setNewAgeLimit(const int& limit);

            /**
             * find the maximum age limit of the room
             * @return - the maximum age limit of the specific kids room
             */
            int getAgeLimit() const;

            /**
             * a destructor for kids room to override the virtual base destructor
             */
            ~KidsRoom() override = default;

            /**
             * returns a ptr to the room according to its type
             */
            EscapeRoomWrapper* clone() const override;
        };
    }
}

#endif //HW4_KIDSROOM_H
