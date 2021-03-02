//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include <vector>
#include "model/user/User.h"
#include "model/room/Room.h"
#include "services/CSVService.h"

int main() {
    vector<User*> users = getUsers();
    vector<Room*> rooms = getRooms(users);

    log("-----------   USERS   ------------");
    for (User* user : users)
        user->printInfo();

    log("-----------   ROOMS   -----------");
    for (Room* room : rooms)
        room->printInfo();
}