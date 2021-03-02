//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../model/rapidcsv.h"

#include "../model/user/Student.h"
#include "../model/user/LabEmployee.h"
#include "../model/user/Professor.h"
#include "../model/user/Director.h"
#include "../model/user/Admin.h"
#include "../model/room/ClassRoom.h"
#include "../model/room/LectureRoom.h"
#include "../model/room/ConferenceRoom.h"
#include "../model/room/Cabinet.h"
#include "../model/room/DirectorCabinet.h"

vector<User*> getUsers() {
    string path = "../hw02/model/user/user_db.csv";
    rapidcsv::Document doc(path, rapidcsv::LabelParams(0, 0));

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

        if (obj[0] == "User")
            user = new User(name, surname, age, accessLevel, extraInfo);
        else if (obj[0] == "Student")
            user = new Student(name, surname, age, course, extraInfo);
        else if (obj[0] == "Lab employee")
            user = new LabEmployee(name, surname, age, lab, isPhd, extraInfo);
        else if (obj[0] == "Professor")
            user = new Professor(name, surname, age, lab, workExperience, extraInfo);
        else if (obj[0] == "Director")
            user = new Director(name, surname, age, extraInfo);
        else if (obj[0] == "Admin")
            user = new Admin(name, surname, age, extraInfo);
        else {
            log(ERROR, "Error with reading file with users. Type of user(" + obj[0] + ") wasn't found.");
            continue;
        }

        users.push_back(user);
    }
    return users;
}

vector<Room*> getRooms(vector<User*> &users) {
    string path = "../hw02/model/room/room_db.csv";
    rapidcsv::Document doc(path, rapidcsv::LabelParams(0, 0));

    vector<Room*> rooms;
    Room *room;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        vector<string> obj = doc.GetRow<string>(i);

        // Parameters from CSV file
        int number = (!obj[0].empty()) ? doc.GetCell<int>(0, i) : 0;
        int fullness = (!obj[3].empty()) ? doc.GetCell<int>(3, i) : 0;
        bool isBooked = obj[4] == "true";

        if (obj[1] == "Class room")
            room = new ClassRoom(number, fullness, isBooked);
        else if (obj[1] == "Lecture room")
            room = new LectureRoom(number, fullness, isBooked);
        else if (obj[1] == "Conference room")
            room = new ConferenceRoom(number, fullness, isBooked);
        else if (obj[1] == "Cabinet") {
            User *owner;
            if (!obj[6].empty()) {
                int id = doc.GetCell<int>(6, i);
                for (User *user : users) {
                    if (user->getId() == id) {
                        owner = user;
                        break;
                    }
                }
            }
            if (owner == nullptr) {
                room = new Cabinet(doc.GetCell<int>(0, i),
                                   Laboratory_nms::toEnum(obj[5]));
            } else {
                room = new Cabinet(doc.GetCell<int>(0, i),
                                   Laboratory_nms::toEnum(obj[5]),
                                   *owner);
            }
        } else if (obj[1] == "Director cabinet") {
            User *owner;
            if (!obj[6].empty()) {
                int id = doc.GetCell<int>(6, i);
                for (User *user : users) {
                    if (user->getId() == id) {
                        owner = user;
                        break;
                    }
                }
            }
            if (owner == nullptr) {
                log(WARNING, "Director cabinet wasn't created, because user wasn't found");
                continue;
            }
            if (owner->getAccessLevel() != Director::ACCESS_LEVEL) {
                log(WARNING, "User isn't director");
                continue;
            }
            room = new DirectorCabinet(*dynamic_cast<Director*>(owner));
        } else {
            log(ERROR, "Error with reading file with rooms. Type of user wasn't found.");
            continue;
        }

        rooms.push_back(room);
    }
    return rooms;
}