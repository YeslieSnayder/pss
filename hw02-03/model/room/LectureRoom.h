//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_LECTUREROOM_H
#define PSS_LECTUREROOM_H

#include "Room.h"

class LectureRoom : public Room {
public:
    static const AccessLevel ACCESS_LEVEL = NO_LEVEL;

    LectureRoom(int number, int floor) : Room(ACCESS_LEVEL, LECTURE_ROOM, number, floor) {}

    LectureRoom(int number, int floor, int fullness, bool isBooked)
        : Room(ACCESS_LEVEL, LECTURE_ROOM, number, floor, fullness, isBooked) {}

    LectureRoom(int number, int floor, int fullness, bool isBooked, vector<int> acceptableUsers)
        : Room(ACCESS_LEVEL, LECTURE_ROOM, number, floor, fullness, isBooked, acceptableUsers) {}
};

#endif //PSS_LECTUREROOM_H
