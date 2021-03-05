//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../services/CSVService.cpp"

/**
 * The test is about reading and conversion from files ".csv".
 * The output contains all data about users and rooms.
 * @return nothing
 * If there is an error, please follow the instructions in README.md file: "Error with reading csv-file".
 */
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