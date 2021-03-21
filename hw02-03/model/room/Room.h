//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_ROOM_H
#define PSS_ROOM_H

#include <vector>
#include "../user/User.h"
#include "../Capacity.h"

class Room {
    AccessLevel accessLevel;
    Capacity capacity;
    int number;
    int floor;
    int fullness = 0;
    bool _isBooked = false;
    vector<int> acceptableUsers;

    static inline bool EMERGENCY_SITUATION = false;

public:

    Room(AccessLevel accessLevel, Capacity capacity, int number, int floor, int fullness, bool isBooked)
            : accessLevel(accessLevel), number(number), capacity(capacity), fullness(fullness),
            _isBooked(isBooked), floor(floor) { }

    Room(AccessLevel accessLevel, Capacity capacity, int number, int floor, int fullness, bool isBooked, vector<int> acceptableUsers)
            : accessLevel(accessLevel), capacity(capacity), number(number), fullness(fullness),
            _isBooked(isBooked), acceptableUsers(acceptableUsers), floor(floor) { }

    Room(AccessLevel accessLevel, Capacity capacity, int number, int floor)
            : accessLevel(accessLevel), number(number), capacity(capacity), floor(floor) { }

    virtual void printInfo() {
        log(Capacity_nms::toString(this->capacity) + ", number: " + std::to_string(number)
            + ", floor: " + std::to_string(floor)
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

    virtual bool isAcceptableUserForThisRoom(User& user) {
        if (EMERGENCY_SITUATION) return true;
        if (user.getAccessLevel() == BLUE && floor == 1
                && (this->capacity == LECTURE_ROOM || this->capacity == CONFERENCE_ROOM))
            return true;
        if (user.getAccessLevel() >= accessLevel && this->capacity != CABINET)
            return true;
        if (user.getAccessLevel() == SUPER_USER)
            return true;
        for (int i : acceptableUsers) {
            if (user.getId() == i)
                return true;
        }
        return false;
    }

    virtual void addAcceptableUser(User& admin, User& user) {
        if (admin.getAccessLevel() == SUPER_USER)
            acceptableUsers.push_back(user.getId());
    }

    static bool isEmergencySituation() {
        return EMERGENCY_SITUATION;
    }

    static void setEmergencySituation(User &admin, bool emergencySituation) {
        if (admin.getAccessLevel() == SUPER_USER)
            EMERGENCY_SITUATION = emergencySituation;
    }

    virtual const vector<int> &getAcceptableUsers() const {
        return acceptableUsers;
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

    virtual int getFloor() const {
        return floor;
    }

    virtual void setAcceptableUsers(User& admin, const vector<int> &acceptableUsers) {
        if (admin.getAccessLevel() == SUPER_USER)
            Room::acceptableUsers = acceptableUsers;
    }

    virtual void setAccessLevel(User& admin, AccessLevel accessLevel) {
        if (admin.getAccessLevel() == SUPER_USER)
            this->accessLevel = accessLevel;
    }

    virtual void setCapacity(User& admin, Capacity capacity) {
        if (admin.getAccessLevel() == SUPER_USER)
            this->capacity = capacity;
    }

    virtual void setNumber(User& admin, int number) {
        if (admin.getAccessLevel() == SUPER_USER)
            this->number = number;
    }

    virtual void setIsBooked(bool isBooked) {
        this->_isBooked = isBooked;
    }

    virtual void setFullness(User& admin, int fullness) {
        if (admin.getAccessLevel() == SUPER_USER)
            this->fullness = fullness;
    }

    virtual void setFloor(User& admin, int floor) {
        if (admin.getAccessLevel() == SUPER_USER)
            this->floor = floor;
    }
};


#endif //PSS_ROOM_H
