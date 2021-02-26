//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_STUDENT_H
#define PSS_STUDENT_H

#include "User.h"

class Student : public User {
    int course;

public:
    static const AccessLevel ACCESS_LEVEL = NO_LEVEL;

    Student(string name, string surname, int age, int course)
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL) {
        this->course = course;
    }
};


#endif //PSS_STUDENT_H
