//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_DIRECTORCABINET_H
#define PSS_DIRECTORCABINET_H

#include "Room.h"
#include "../user/Director.h"

class DirectorCabinet : public Room {
protected:
    Director owner;
public:
    static const AccessLevel ACCESS_LEVEL = RED;

    DirectorCabinet(int number, int floor, Director& owner)
        : Room(ACCESS_LEVEL, DIRECTOR_CABINET, number, floor), owner(owner) {}

    DirectorCabinet(int number, int floor, Director& owner, vector<int> acceptableUsers)
            : Room(ACCESS_LEVEL, DIRECTOR_CABINET, number, floor, 0, true, acceptableUsers),
            owner(owner) {}


    const Director &getOwner() const;
    void setOwner(const Director &owner);
};

const Director &DirectorCabinet::getOwner() const {
    return owner;
}

void DirectorCabinet::setOwner(const Director &owner) {
    DirectorCabinet::owner = owner;
}

#endif //PSS_DIRECTORCABINET_H
