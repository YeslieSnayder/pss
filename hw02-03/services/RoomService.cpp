//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../model/room/WrongAccessException.h"
#include "../model/room/Cabinet.h"

/**
 * The method allows user to get access to the room
 * @param user - person who wants to get an access to room
 * @param room - the room that user wants to enter
 */
void enterRoom(User *user, Room *room) {
    bool isAcceptableUser = room->isAcceptableUserForThisRoom(*user);
    if (user->getAccessLevel() < room->getAccessLevel() && !isAcceptableUser) {
        throw WrongAccessException(*user, *room);
    }
    if (room->isBooked() && room->getFullness() == room->getCapacity() && user->getAccessLevel() != SUPER_USER) {
        log(WARNING, "Sorry, the room " + to_string(room->getNumber())
            + " is booked and full, so user " + user->getName() + " cannot come in");
        return;
    }
    if (room->getAccessLevel() == Cabinet::ACCESS_LEVEL && user->getAccessLevel() != SUPER_USER && !isAcceptableUser) {
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

/**
 * The method allows user to leave a room
 * @param user - person who wants to leave the room
 * @param room - the room that user wants to leave from
 */
void leaveRoom(User *user, Room *room) {
    if (!room->isBooked() or room->getFullness() == 0) {
        log(WARNING, "No people in a room #" + to_string(room->getNumber())
            + ", therefore user " + user->getName() + " cannot leave the room");
        return;
    }

    room->decreaseFullness();
    if (room->getFullness() == 0)
        room->setIsBooked(false);

    log(INFO, "User " + user->getName() + " has left the room #" + to_string(room->getNumber()));
}

void setEmergencySituation(User *user, bool isEmergency) {
    if (user->getAccessLevel() == SUPER_USER) {
        Room::setEmergencySituation(*user, isEmergency);
    }
}

vector<Room*> getAcceptableRooms(vector<Room*> rooms, User* user) {
    vector<Room*> res;
    for (auto & room : rooms) {
        if (room->isAcceptableUserForThisRoom(*user))
            res.push_back(room);
    }
    return res;
}