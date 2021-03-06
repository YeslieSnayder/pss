//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../model/user/Student.h"
#include "../model/user/LabEmployee.h"
#include "../model/user/Professor.h"
#include "../model/user/Director.h"
#include "../model/room/ClassRoom.h"
#include "../model/room/LectureRoom.h"
#include "../model/room/ConferenceRoom.h"
#include "../model/room/Cabinet.h"
#include "../model/room/DirectorCabinet.h"
#include "../model/user/Admin.h"

void toLowerCase(string &str);

User *createUser(string type, string name, string surname, int age, AccessLevel accessLevel, int course,
                 Laboratory lab, int workExperience, bool isPhd, string extraInfo="", string password=".") {
    toLowerCase(type);

    string userType = Student::TYPE;
    toLowerCase(userType);
    if (type == userType)
        return new Student(name, surname, age, course, extraInfo);

    userType = LabEmployee::TYPE;
    toLowerCase(userType);
    if (type == userType)
        return new LabEmployee(name, surname, age, lab, isPhd, extraInfo);

    userType = Professor::TYPE;
    toLowerCase(userType);
    if (type == userType)
        return new Professor(name, surname, age, lab, workExperience, extraInfo);

    userType = Director::TYPE;
    toLowerCase(userType);
    if (type == userType)
        return new Director(name, surname, age, extraInfo);

    userType = Admin::TYPE;
    toLowerCase(userType);
    if (type == userType)
        return new Admin(name, surname, age, extraInfo, password);

    userType = User::TYPE;
    toLowerCase(userType);
    if (type == userType)
        return new User(name, surname, age, accessLevel, extraInfo);
    log(WARNING, "User was not created. Type of user: " + type + " doesn't exist.");
    return nullptr;
}

Room *createRoom(string type, int number, int fullness, bool isBooked, Laboratory lab, User *owner, vector<int> userIds) {
    if (type == Capacity_nms::toString(CLASS_ROOM))
        return new ClassRoom(number, fullness, isBooked, userIds);
    else if (type == Capacity_nms::toString(LECTURE_ROOM))
        return new LectureRoom(number, fullness, isBooked, userIds);
    else if (type == Capacity_nms::toString(CONFERENCE_ROOM))
        return new ConferenceRoom(number, fullness, isBooked, userIds);
    else if (type == Capacity_nms::toString(CABINET)) {
        if (owner == nullptr)
            return new Cabinet(number, lab, userIds);
        else
            return new Cabinet(number, lab, *owner, userIds);
    } else if (type == Capacity_nms::toString(DIRECTOR_CABINET)) {
        if (owner == nullptr) {
            log(WARNING, "Director cabinet wasn't created, because user wasn't found.");
            return nullptr;
        }
        if (owner->getAccessLevel() < Director::ACCESS_LEVEL) {
            log(WARNING, "User isn't director.");
            return nullptr;
        }
        return new DirectorCabinet(number, *dynamic_cast<Director*>(owner), userIds);
    }
    log(WARNING, "Room wasn't created. Type of room: " + type + " doesn't exist.");
    return nullptr;
}

Room *createRoom(string type, int number, int fullness, bool isBooked, Laboratory lab, User *owner) {
    if (type == Capacity_nms::toString(CLASS_ROOM))
        return new ClassRoom(number, fullness, isBooked);
    else if (type == Capacity_nms::toString(LECTURE_ROOM))
        return new LectureRoom(number, fullness, isBooked);
    else if (type == Capacity_nms::toString(CONFERENCE_ROOM))
        return new ConferenceRoom(number, fullness, isBooked);
    else if (type == Capacity_nms::toString(CABINET)) {
        if (owner == nullptr)
            return new Cabinet(number, lab);
        else
            return new Cabinet(number, lab, *owner);
    } else if (type == Capacity_nms::toString(DIRECTOR_CABINET)) {
        if (owner == nullptr) {
            log(WARNING, "Director cabinet wasn't created, because user wasn't found.");
            return nullptr;
        }
        if (owner->getAccessLevel() < Director::ACCESS_LEVEL) {
            log(WARNING, "User isn't director.");
            return nullptr;
        }
        return new DirectorCabinet(number, *dynamic_cast<Director*>(owner));
    }
    log(WARNING, "Room wasn't created. Type of room: " + type + " doesn't exist.");
    return nullptr;
}

string toLowerCase(const string& str) {
    string res = str;
    for (char &i : res) {
        if (i >= 'A' && i <= 'Z')
            i = i - 'A' + 'a';
    }
    return res;
}

void toLowerCase(string &str) {
    for (char &i : str) {
        if (i >= 'A' && i <= 'Z')
            i = i - 'A' + 'a';
    }
}