//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../model/rapidcsv.h"
#include "CreatorService.cpp"

const string USER_DB_FILEPATH = "../hw02/model/user/user_db.csv";
const string ROOM_DB_FILEPATH = "../hw02/model/room/room_db.csv";

vector<User*> getUsers() {
    rapidcsv::Document doc(USER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

    vector<User*> users;
    User *user;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        vector<string> obj = doc.GetRow<string>(i);

        // Parameters from CSV file
        string name = obj[1], surname = obj[2];
        int age = doc.GetCell<int>(3, i);
        AccessLevel accessLevel = AccessLevel_nms::toEnum(obj[4]);
        int course = (!obj[5].empty()) ? doc.GetCell<int>(5, i) : 0;
        Laboratory lab = Laboratory_nms::toEnum(obj[6]);
        int workExperience = (!obj[7].empty()) ? doc.GetCell<int>(7, i) : 0;
        bool isPhd = obj[8] == "true";
        string extraInfo = obj[9];
        string password = obj[10];

        // Create an user
        user = createUser(obj[0], name, surname, age, accessLevel, course, lab, workExperience, isPhd, extraInfo, password);
        if (user != nullptr)
            users.push_back(user);
        else
            log(WARNING, "Problem with reading file with users. Type of user(" + obj[0] + ") wasn't found.");
    }
    return users;
}

vector<Room*> getRooms() {
    rapidcsv::Document doc(ROOM_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

    vector<Room*> rooms;
    Room *room;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        vector<string> obj = doc.GetRow<string>(i);

        // Parameters from CSV file
        string type =  obj[1];
        int number = (!obj[0].empty()) ? doc.GetCell<int>(0, i) : 0;
        int fullness = (!obj[3].empty()) ? doc.GetCell<int>(3, i) : 0;
        bool isBooked = obj[4] == "true";
        Laboratory lab = Laboratory_nms::toEnum(obj[5]);
        if (obj[1] == Capacity_nms::toString(DIRECTOR_CABINET)) {
            continue;
        }

        // Create a room
        room = createRoom(type, number, fullness, isBooked, lab, nullptr);
        if (room != nullptr)
            rooms.push_back(room);
        else
            log(WARNING, "Problem with reading file with rooms. Type of room: " + obj[0] + " wasn't found.");
    }
    return rooms;
}

vector<Room*> getRooms(vector<User*> &users) {
    rapidcsv::Document doc(ROOM_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

    vector<Room*> rooms;
    Room *room;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        vector<string> obj = doc.GetRow<string>(i);

        // Parameters from CSV file
        string type =  obj[1];
        int number = (!obj[0].empty()) ? doc.GetCell<int>(0, i) : 0;
        int fullness = (!obj[3].empty()) ? doc.GetCell<int>(3, i) : 0;
        bool isBooked = obj[4] == "true";
        Laboratory lab = Laboratory_nms::toEnum(obj[5]);
        User *owner = nullptr;
        if (obj[1] == Capacity_nms::toString(CABINET)
                || obj[1] == Capacity_nms::toString(DIRECTOR_CABINET)) {
            if (!obj[6].empty()) {
                int id = doc.GetCell<int>(6, i);
                for (User *user : users) {
                    if (user->getAccessLevel() >= LabEmployee::ACCESS_LEVEL && user->getId() == id) {
                        owner = user;
                        break;
                    }
                }
            }
        }

        // Create a room
        room = createRoom(type, number, fullness, isBooked, lab, owner);
        if (room != nullptr)
            rooms.push_back(room);
        else
            log(WARNING, "Problem with reading file with rooms. Type of room(" + obj[0] + ") wasn't found.");
    }
    return rooms;
}