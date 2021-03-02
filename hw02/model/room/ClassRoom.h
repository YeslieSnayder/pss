//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_CLASSROOM_H
#define PSS_CLASSROOM_H

#include "Room.h"

class ClassRoom : public Room {
public:
    static const AccessLevel ACCESS_LEVEL = NO_LEVEL;

    ClassRoom(int number) : Room(ACCESS_LEVEL, CLASS_ROOM, number) {}

    ClassRoom(int number, int fullness, bool isBooked) : Room(ACCESS_LEVEL, CLASS_ROOM, number, fullness, isBooked) {}
};

#endif //PSS_CLASSROOM_H
