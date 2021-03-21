//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_CONFERENCEROOM_H
#define PSS_CONFERENCEROOM_H

#include "Room.h"

class ConferenceRoom : public Room {
public:
    static const AccessLevel ACCESS_LEVEL = YELLOW;

    ConferenceRoom(int number, int floor) : Room(ACCESS_LEVEL, CONFERENCE_ROOM, number, floor) {}

    ConferenceRoom(int number, int floor, int fullness, bool isBooked)
        : Room(ACCESS_LEVEL, CONFERENCE_ROOM, number, floor, fullness, isBooked) {}

    ConferenceRoom(int number, int floor, int fullness, bool isBooked, vector<int> acceptableUsers)
        : Room(ACCESS_LEVEL, CONFERENCE_ROOM, number, floor, fullness, isBooked, acceptableUsers) {}
};


#endif //PSS_CONFERENCEROOM_H
