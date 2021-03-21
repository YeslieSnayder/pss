//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../services/CSVService.cpp"
#include "../services/RoomService.cpp"

User* getRandomUserOfType(vector<User*> users, AccessLevel level);

/**
 * Testing the abilities of admin to give an access for user.
 */
int main() {
    vector<User*> users = getUsers();
    User* owner = getRandomUserOfType(users, LabEmployee::ACCESS_LEVEL);
    Room* room = new Cabinet(0, 2, *owner);
    User* user = getRandomUserOfType(users, Student::ACCESS_LEVEL);
    Admin* admin = dynamic_cast<Admin*>(getRandomUserOfType(users, Admin::ACCESS_LEVEL));

    log("-----------   Usual access of user   ------------");
    try {
        enterRoom(owner, room);
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("-----------   After changing access   ------------");
    admin->giveAccess(*user, *room);
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }
}

User* getRandomUserOfType(vector<User*> users, AccessLevel level) {
    vector<User*> arr;
    for (auto & user : users) {
        if (user->getAccessLevel() == level) {
            arr.push_back(user);
        }
    }
    return arr[rand() % arr.size()];
}