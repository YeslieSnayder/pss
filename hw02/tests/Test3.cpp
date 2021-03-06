//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../services/CSVService.cpp"
#include "../services/RoomService.cpp"

void testAccess(User *user, vector<Room*> rooms);
User* getRandomUserOfType(vector<User*> users, AccessLevel level);

/**
 * Testing access levels of all types of users.
 * @return
 */
int main() {
    vector<User*> users = getUsers();
    vector<Room*> rooms = getRooms(users);

    log("-----------   Student   ------------");
    testAccess(getRandomUserOfType(users, Student::ACCESS_LEVEL), rooms);
    log("-----------   Lab employee   ------------");
    testAccess(getRandomUserOfType(users, LabEmployee::ACCESS_LEVEL), rooms);
    log("-----------   Professor   ------------");
    testAccess(getRandomUserOfType(users, Professor::ACCESS_LEVEL), rooms);
    log("-----------   Director   ------------");
    testAccess(getRandomUserOfType(users, Director::ACCESS_LEVEL), rooms);
    log("-----------   Admin   ------------");
    testAccess(getRandomUserOfType(users, Admin::ACCESS_LEVEL), rooms);
}

/**
 * Testing of access level of the user. The method prints all supporting information.
 */
void testAccess(User *user, vector<Room*> rooms) {
    log("-----------   Entering room   ------------");
    for (Room* room : rooms) {
        try {
            enterRoom(user, room);
        } catch (WrongAccessException ex) {
            log(ERROR, ex.message());
        }
    }

    log("-----------   Leaving room   ------------");
    for (Room* room : rooms) {
        try {
            leaveRoom(user, room);
        } catch (WrongAccessException ex) {
            log(ERROR, ex.message());
        }
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