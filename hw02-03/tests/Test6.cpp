//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include <ctime>

#include "../services/CSVService.cpp"
#include "../services/RoomService.cpp"

User* getRandomUser(vector<User*> &users);
void test(User *user);

/**
 * Testing 'Emergency situation' feature.
 */
int main() {
    srand(time(0));

    vector<User*> users = getUsers();
    User* user = getRandomUser(users);

    log("");
    log("-----------   Usual access of user: " + user->TYPE + "   ------------");
    log("");

    test(user);

    log("");
    log("-----   Access of " + user->TYPE + " after setting emergency situation   -----");
    log("");

    User *admin = new Admin("pass");
    Room::setEmergencySituation(*admin, true);

    test(user);
}

void test(User *user) {
    Room* room;
    User* owner;

    log("-----------------   CLASS ROOM   -----------------");
    room = new ClassRoom(0, 1);
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("----------   LECTURE ROOM (floor = 1)   ----------");
    room = new LectureRoom(0, 1);
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("----------   LECTURE ROOM (floor = 2)   ----------");
    room = new LectureRoom(0, 2);
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("---------   CONFERENCE ROOM (floor = 1)   --------");
    room = new ConferenceRoom(0, 1);
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("--------   CONFERENCE ROOM (floor = 10)   --------");
    room = new ConferenceRoom(0, 10);
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("-------------------   CABINET   ------------------");
    room = new Cabinet(0, 1,
                       *(new LabEmployee("test", "test", 5, AGLA, false)));
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }

    log("--------------   DIRECTOR CABINET   --------------");
    room = new DirectorCabinet(0, 1, *(new Director("test", "test", 10)));
    try {
        enterRoom(user, room);
    } catch (WrongAccessException e) {
        log(ERROR, e.message());
    }
}


User* getRandomUser(vector<User*> &users) {
    return users[rand() % users.size()];
}
