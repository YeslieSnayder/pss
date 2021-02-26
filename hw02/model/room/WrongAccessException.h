//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_WRONGACCESSEXCEPTION_H
#define PSS_WRONGACCESSEXCEPTION_H

#include "Room.h"
#include "../user/User.h"

class WrongAccessException : public exception {
    User user;
    Room room;

public:
    WrongAccessException(User user, Room room) : user(user), room(room) { }

    string message() {
        return "The user " + user.getName() + " (" + AccessLevel_nms::toString(user.getAccessLevel())
            + ") tried to access the room " + to_string(room.getNumber())
            + " (" + AccessLevel_nms::toString(room.getAccessLevel())
            + ") to which (s)he does not have access";
    }
};

#endif //PSS_WRONGACCESSEXCEPTION_H
