//
// Created by Andrey Kuzmickiy on 20.02.2021.
//

#ifndef PSS_ROOM_H
#define PSS_ROOM_H

#include "../AccessLevel.h"

enum Capacity {
    CLASS_ROOM = 25,        // <= 25 people,  access = NO_LEVEL
    LECTURE_ROOM = 250,     // <= 250 people, access = NO_LEVEL
    CABINET = 50,           // <= 50 people,  access = GREEN
    CONFERENCE_ROOM = 100,  // <= 100 people, access = YELLOW
    DIRECTOR_CABINET = 5    // <= 5 people,   access = RED
};

class Room {
    AccessLevel accessLevel;
    Capacity capacity;
    int number;
    int fullness = 0;
    bool isBooked1 = false;

public:
    Room(AccessLevel accessLevel, Capacity capacity, int number)
        : accessLevel(accessLevel), number(number), capacity(capacity) { }

    void book() {
        isBooked1 = true;
    }

    AccessLevel getAccessLevel() const {
        return accessLevel;
    }

    Capacity getCapacity() const {
        return capacity;
    }

    int getNumber() const {
        return number;
    }

    bool isBooked() const {
        return isBooked1;
    }

    int getFullness() const {
        return fullness;
    }

    void setAccessLevel(AccessLevel accessLevel) {
        Room::accessLevel = accessLevel;
    }

    void setCapacity(Capacity capacity) {
        Room::capacity = capacity;
    }

    void setNumber(int number) {
        Room::number = number;
    }

    void setFullness(int fullness) {
        Room::fullness = fullness;
    }

    void setIsBooked(bool isBooked) {
        isBooked1 = isBooked;
    }
};


#endif //PSS_ROOM_H
