//
// Created by Andrey Kuzmickiy group BS20-03.
//

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

User *createUser(string type, string name, string surname, int age, AccessLevel accessLevel, int course,
                 Laboratory lab, int workExperience, bool isPhd, string extraInfo) {
    if (type == Student::TYPE)
        return new Student(name, surname, age, course, extraInfo);
    else if (type == LabEmployee::TYPE)
        return new LabEmployee(name, surname, age, lab, isPhd, extraInfo);
    else if (type == Professor::TYPE)
        return new Professor(name, surname, age, lab, workExperience, extraInfo);
    else if (type == Director::TYPE)
        return new Director(name, surname, age, extraInfo);
    else if (type == Admin::TYPE)
        return new Admin(name, surname, age, extraInfo);
    else if (type == User::TYPE)
        return new User(name, surname, age, accessLevel, extraInfo);
    log(WARNING, "User was not created. Type of user: " + type + " doesn't exist.");
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