//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_ROOM_H
#define PSS_ROOM_H

#include "../user/User.h"
#include "../Capacity.h"

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
            + ", _isBooked: " + (_isBooked ? "true" : "false"));
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
        this->_isBooked = isBooked;
    }

    virtual void setFullness(User& user, int fullness) {
        if (user.getAccessLevel() == SUPER_USER)
            this->fullness = fullness;
    }
};


#endif //PSS_ROOM_H
