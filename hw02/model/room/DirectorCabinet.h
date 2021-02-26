//
// Created by yesliesnayder on 26.02.2021.
//

#ifndef PSS_DIRECTORCABINET_H
#define PSS_DIRECTORCABINET_H

#include "Room.h"
#include "../user/Director.h"

/**
 * Singleton class because there can be only one director
 */
class DirectorCabinet : public Room {
protected:
    Director owner;

    static DirectorCabinet* instance;
    DirectorCabinet(Director& owner) : Room(ACCESS_LEVEL, DIRECTOR_CABINET, -1), owner(owner) {}

public:
    static const AccessLevel ACCESS_LEVEL = RED;

    DirectorCabinet(DirectorCabinet &other) = delete;
    void operator=(const DirectorCabinet&) = delete;

    static DirectorCabinet *getInstance(Director _owner);

    const Director &getOwner() const;

    void setOwner(const Director &owner);
};

DirectorCabinet *DirectorCabinet::instance = nullptr;
DirectorCabinet *DirectorCabinet::getInstance(Director _owner) {
    if (instance == nullptr) {
        instance = new DirectorCabinet(_owner);
    }
    return instance;
}

const Director &DirectorCabinet::getOwner() const {
    return owner;
}

void DirectorCabinet::setOwner(const Director &owner) {
    DirectorCabinet::owner = owner;
}

#endif //PSS_DIRECTORCABINET_H
