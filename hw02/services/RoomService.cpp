//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../model/AccessLevel.h"
#include "../model/user/User.h"
#include "../model/room/WrongAccessException.h"
#include "../model/room/Cabinet.h"

void enterRoom(User *user, Room *room) {
    if (user->getAccessLevel() < room->getAccessLevel()) {
        throw WrongAccessException(*user, *room);
    }
    if (room->isBooked() && room->getFullness() == room->getCapacity()) {
        log(WARNING, "Sorry, the room is booked and user " + user->getName()
            + " cannot come in, because room " + to_string(room->getNumber()) + " is full");
        return;
    }
    if (room->getAccessLevel() == Cabinet::ACCESS_LEVEL) {
        Cabinet* cabinet = static_cast<Cabinet*>(room);

        if (user->getAccessLevel() == LabEmployee::ACCESS_LEVEL) {
            LabEmployee* employee = static_cast<LabEmployee*>(user);
            if (cabinet->getLaboratory() != employee->getLaboratory())
                throw WrongAccessException(*user, *room);
        } else if (user->getId() != cabinet->getOwner().getId()) {
            throw WrongAccessException(*user, *room);
        }
    }
    if (!room->isBooked())
        room->book();
    room->increaseFullness();

    log(INFO,"User " + user->getName()
        + " entered the room #" + to_string(room->getNumber()) + " successfully");
}

void leaveRoom(User *user, Room *room) {
    if (!room->isBooked() or room->getFullness() == 0) {
        log(WARNING, "No people in a room #" + to_string(room->getNumber())
            + ", therefore user " + user->getName() + " cannot leave the room");
        return;
    }

    if (user->getAccessLevel() < room->getAccessLevel()) {
        throw WrongAccessException(*user, *room);
    }

    room->decreaseFullness();
    if (room->getFullness() == 0)
        room->setIsBooked(false);

    log(INFO, "User " + user->getName() + " has left the room #" + to_string(room->getNumber()));
}