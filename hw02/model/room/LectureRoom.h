//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_LECTUREROOM_H
#define PSS_LECTUREROOM_H

#include "Room.h"

class LectureRoom : public Room {
public:
    static const AccessLevel ACCESS_LEVEL = NO_LEVEL;

    LectureRoom(int number) : Room(ACCESS_LEVEL, LECTURE_ROOM, number) {}

    LectureRoom(int number, int fullness, bool isBooked) : Room(ACCESS_LEVEL, LECTURE_ROOM, number, fullness, isBooked) {}
};

#endif //PSS_LECTUREROOM_H
