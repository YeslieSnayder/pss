//
// Created by yesliesnayder on 20.02.2021.
//

#include <iostream>
#include "model/user/User.h"
#include "model/room/WrongAccessException.h"

void enterRoom(User user, Room room) {
    if (user.getAccessLevel() < room.getAccessLevel()) {
        throw WrongAccessException(user, room);
    }
    if (room.isBooked() && room.getFullness() == room.getCapacity()) {
        std::cout << "Sorry, the room is booked and user " << user.getName() << " cannot come in, because room "
            << room.getNumber() << " is full";
    }

    if (!room.isBooked()) room.book();
    room.setFullness(room.getFullness() + 1);

    std::cout << "Access has given successful";
}