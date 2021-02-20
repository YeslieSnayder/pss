//
// Created by yesliesnayder on 20.02.2021.
//

/*
CLASS_ROOM = 25,        // <= 25 people,  access = NO_LEVEL
LECTURE_ROOM = 250,     // <= 250 people, access = NO_LEVEL
CABINET = 50,           // <= 50 people,  access = GREEN
CONFERENCE_ROOM = 100,  // <= 100 people, access = YELLOW
DIRECTOR_CABINET = 5    // <= 5 people,   access = RED
 */

#ifndef PSS_CUSTOMROOMS_H
#define PSS_CUSTOMROOMS_H

#include "Room.h"

class ClassRoom : public Room {
public:
    ClassRoom(int number) : Room(NO_LEVEL, CLASS_ROOM, number) {}
};

class LectureRoom : public Room {
public:
    LectureRoom(int number) : Room(NO_LEVEL, LECTURE_ROOM, number) {}
};

class Cabinet : public Room {
public:
    Cabinet(int number) : Room(GREEN, CABINET, number) {}
};

class ConferenceRoom : public Room {
public:
    ConferenceRoom(int number) : Room(YELLOW, CONFERENCE_ROOM, number) {}
};

class DirectorCabinet : public Room {
public:
    DirectorCabinet() : Room(RED, DIRECTOR_CABINET, -1) {}
};

#endif //PSS_CUSTOMROOMS_H
