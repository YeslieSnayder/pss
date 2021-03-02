//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_STUDENT_H
#define PSS_STUDENT_H

#include <utility>

#include "User.h"

class Student : public User {
    uint8_t course;

public:
    static const AccessLevel ACCESS_LEVEL = NO_LEVEL;

    Student(string name, string surname, int age, int course, string extraInfo="")
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)) {
        this->course = course;
    }

    int getCourse() const {
        return course;
    }

    void setCourse(int course) {
        Student::course = course;
    }

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: Student"
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + ", course: " + to_string(course)
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }
};


#endif //PSS_STUDENT_H
