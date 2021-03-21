//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_CLASSROOM_H
#define PSS_CLASSROOM_H

#include "Room.h"

class ClassRoom : public Room {
public:
    static const AccessLevel ACCESS_LEVEL = NO_LEVEL;

    ClassRoom(int number, int floor) : Room(ACCESS_LEVEL, CLASS_ROOM, number, floor) {}

    ClassRoom(int number, int floor, int fullness, bool isBooked)
        : Room(ACCESS_LEVEL, CLASS_ROOM, number, floor, fullness, isBooked) {}

    ClassRoom(int number, int floor, int fullness, bool isBooked, vector<int> acceptableUsers)
        : Room(ACCESS_LEVEL, CLASS_ROOM, number, floor, fullness, isBooked, acceptableUsers) {}
};

#endif //PSS_CLASSROOM_H
