//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_CONFERENCEROOM_H
#define PSS_CONFERENCEROOM_H

#include "Room.h"

class ConferenceRoom : public Room {
public:
    static const AccessLevel ACCESS_LEVEL = YELLOW;

    ConferenceRoom(int number) : Room(ACCESS_LEVEL, CONFERENCE_ROOM, number) {}

    ConferenceRoom(int number, int fullness, bool isBooked) : Room(ACCESS_LEVEL, CONFERENCE_ROOM, number, fullness, isBooked) {}
};


#endif //PSS_CONFERENCEROOM_H
