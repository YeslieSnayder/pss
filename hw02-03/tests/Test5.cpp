//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../services/CSVService.cpp"
#include "../services/RoomService.cpp"

User* getRandomUserOfType(vector<User*> &users, AccessLevel level);

/**
 * Testing opportunities of guest to get an access to rooms with different floor and access level.
 */
int main() {
    vector<User*> users = getUsers();
    User* guest = getRandomUserOfType(users, Guest::ACCESS_LEVEL);
    Room* room;
    User* owner;

    log("-----------   Usual access of guest   ------------");
    log("");

    log("-----------------   CLASS ROOM   -----------------");
    room = new ClassRoom(0, 1);
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("----------   LECTURE ROOM (floor = 1)   ----------");
    room = new LectureRoom(0, 1);
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("----------   LECTURE ROOM (floor = 2)   ----------");
    room = new LectureRoom(0, 2);
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("---------   CONFERENCE ROOM (floor = 1)   ---------");
    room = new ConferenceRoom(0, 1);
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("---------   CONFERENCE ROOM (floor = 10)   ---------");
    room = new ConferenceRoom(0, 10);
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("-------------------   CABINET   -------------------");
    owner = getRandomUserOfType(users, LabEmployee::ACCESS_LEVEL);
    room = new Cabinet(0, 1, *owner);
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("---------------   DIRECTOR CABINET   ---------------");
    owner = getRandomUserOfType(users, Director::ACCESS_LEVEL);
    room = new DirectorCabinet(0, 1, *dynamic_cast<Director*>(owner));
    try {
        enterRoom(guest, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }
}

User* getRandomUserOfType(vector<User*> &users, AccessLevel level) {
    vector<User*> arr;
    for (auto & user : users) {
        if (user->getAccessLevel() == level) {
            arr.push_back(user);
        }
    }
    return arr[rand() % arr.size()];
}