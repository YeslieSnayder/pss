//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include <vector>
#include "model/rapidcsv.h"

#include "model/user/User.h"
#include "model/user/Student.h"
#include "model/user/LabEmployee.h"
#include "model/user/Professor.h"
#include "model/user/Director.h"
#include "model/user/Admin.h"
#include "model/room/ClassRoom.h"
#include "model/room/LectureRoom.h"
#include "model/room/ConferenceRoom.h"
#include "model/room/Cabinet.h"
#include "model/room/DirectorCabinet.h"

vector<User*> getUsers();
vector<Room*> getRooms(vector<User*> &users);

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

vector<User*> getUsers() {
    string path = "hw02/model/user/user_db.csv";
    rapidcsv::Document doc(path, rapidcsv::LabelParams(0, 0));

    vector<User*> users;
    User *user;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        vector<string> obj = doc.GetRow<string>(i);
        if (obj[0] == "User")
            user = new User(obj[1], obj[2],
                            doc.GetCell<int>(3, i),
                            AccessLevel_nms::toEnum(obj[4]));
        else if (obj[0] == "Student")
            user = new Student(obj[1], obj[2],
                               doc.GetCell<int>(3, i),
                               doc.GetCell<int>(5, i));
        else if (obj[0] == "Lab employee")
            user = new LabEmployee(obj[1], obj[2],
                                   doc.GetCell<int>(3, i),
                                   Laboratory_nms::toEnum(obj[9]),
                                   obj[10] == "true",
                                   obj[11]);
        else if (obj[0] == "Professor")
            user = new Professor(obj[1], obj[2],
                                 doc.GetCell<int>(3, i),
                                 obj[7],
                                 doc.GetCell<int>(8, i));
        else if (obj[0] == "Director")
            user = new Director(obj[1], obj[2], doc.GetCell<int>(3, i));
        else if (obj[0] == "Admin")
            user = new Admin(obj[1], obj[2], doc.GetCell<int>(3, i));
        else {
            log(true, "Error with reading file with users. Type of user wasn't found.");
            continue;
        }

        users.push_back(user);
    }
    return users;
}

vector<Room*> getRooms(vector<User*> &users) {
    string path = "hw02/model/room/room_db.csv";
    rapidcsv::Document doc(path, rapidcsv::LabelParams(0, 0));

    vector<Room*> rooms;
    Room *room;
    for (int i = 0; i < doc.GetRowCount(); i++) {
        vector<string> obj = doc.GetRow<string>(i);
        if (obj[1] == "Class room")
            room = new ClassRoom(doc.GetCell<int>(0, i),
                                 doc.GetCell<int>(3, i),
                                 obj[4] == "true");
        else if (obj[1] == "Lecture room")
            room = new LectureRoom(doc.GetCell<int>(0, i),
                                   doc.GetCell<int>(3, i),
                                   obj[4] == "true");
        else if (obj[1] == "Conference room")
            room = new ConferenceRoom(doc.GetCell<int>(0, i),
                                      doc.GetCell<int>(3, i),
                                      obj[4] == "true");
        else if (obj[1] == "Cabinet") {
            User *owner;
            int id = doc.GetCell<int>(6, i);
            for (User *user : users) {
                if (user->getId() == id) {
                    owner = user;
                    break;
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
            int id = doc.GetCell<int>(6, i);
            for (User *user : users) {
                if (user->getId() == id) {
                    owner = user;
                    break;
                }
            }
            if (owner == nullptr) {
                log(true, "Director cabinet wasn't created, because user wasn't found");
                continue;
            }
            if (owner->getAccessLevel() != Director::ACCESS_LEVEL) {
                log(true, "User isn't director");
                continue;
            }
            room = DirectorCabinet::getInstance(*dynamic_cast<Director*>(owner));
        } else {
            log(true, "Error with reading file with rooms. Type of user wasn't found.");
            continue;
        }

        rooms.push_back(room);
    }
    return rooms;
}