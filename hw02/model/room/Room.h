//
// Created by Andrey Kuzmickiy on 20.02.2021.
//

#ifndef PSS_ROOM_H
#define PSS_ROOM_H

#include "../user/User.h"

enum Capacity {
    CLASS_ROOM = 25,        // <= 25 people,  access = NO_LEVEL
    LECTURE_ROOM = 200,     // <= 200 people, access = NO_LEVEL
    CONFERENCE_ROOM = 50,   // <= 50 people, access = YELLOW
    CABINET = 5,            // <= 5 people,   access = RED
    DIRECTOR_CABINET = 1    // <= 1 person,   access = RED
};

namespace Capacity_nms {

    std::string toString(Capacity capacity) {
        switch (capacity) {
            case CLASS_ROOM: return "Class room";
            case LECTURE_ROOM: return "Lecture room";
            case CONFERENCE_ROOM: return "Conference room";
            case CABINET: return "Cabinet";
            case DIRECTOR_CABINET: return "Director cabinet";

            default: return "No such capacity";
        }
    }

    Capacity toEnum(std::string capacity) {
        if (capacity == "Class room")
            return CLASS_ROOM;
        if (capacity == "Lecture room")
            return LECTURE_ROOM;
        if (capacity == "Conference room")
            return CONFERENCE_ROOM;
        if (capacity == "Cabinet")
            return CABINET;
        if (capacity == "Director cabinet")
            return DIRECTOR_CABINET;
        return CLASS_ROOM;
    }
}

class Room {
    AccessLevel accessLevel;
    Capacity capacity;
    int number;
    int fullness = 0;
    bool _isBooked = false;

public:
    Room(AccessLevel accessLevel, Capacity capacity, int number, int fullness, bool isBooked)
            : accessLevel(accessLevel), number(number), capacity(capacity), fullness(fullness), _isBooked(isBooked) { }

    Room(AccessLevel accessLevel, Capacity capacity, int number)
            : accessLevel(accessLevel), number(number), capacity(capacity) { }

    virtual void printInfo() {
        log(Capacity_nms::toString(this->capacity) + ", number: " + std::to_string(number)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + ", fullness: " + std::to_string(fullness)
            + ", isBooked: " + (_isBooked ? "true" : "false"));
    }

    virtual void book() {
        _isBooked = true;
    }

    virtual void increaseFullness() {
        this->fullness++;
    }

    virtual void decreaseFullness() {
        this->fullness--;
    }

    virtual AccessLevel getAccessLevel() const {
        return accessLevel;
    }

    virtual Capacity getCapacity() const {
        return capacity;
    }

    virtual int getNumber() const {
        return number;
    }

    virtual bool isBooked() const {
        return _isBooked;
    }

    virtual int getFullness() const {
        return fullness;
    }

    virtual void setAccessLevel(User& user, AccessLevel accessLevel) {
        if (user.getAccessLevel() == SUPER_USER)
            this->accessLevel = accessLevel;
    }

    virtual void setCapacity(User& user, Capacity capacity) {
        if (user.getAccessLevel() == SUPER_USER)
            this->capacity = capacity;
    }

    virtual void setNumber(User& user, int number) {
        if (user.getAccessLevel() == SUPER_USER)
            this->number = number;
    }

    virtual void setIsBooked(bool isBooked) {
        _isBooked = isBooked;
    }

    virtual void setFullness(User& user, int fullness) {
        if (user.getAccessLevel() == SUPER_USER)
            this->fullness = fullness;
    }
};


#endif //PSS_ROOM_H
