//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_PROFESSOR_H
#define PSS_PROFESSOR_H

#include <utility>

#include "User.h"
#include "Student.h"

class Professor : public User {
    int workExperience;
    vector<Student> teacherPet;
    string subject;

public:
    static const AccessLevel ACCESS_LEVEL = YELLOW;

    Professor(string name, string surname, int age, string subject, int workExperience, vector<Student> teacherPet)
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL) {
        this->workExperience = workExperience;
        this->teacherPet = std::move(teacherPet);
        this->subject = std::move(subject);
    }

    Professor(const string& name, const string& surname, int age, const string& subject, int workExperience)
            : User(name, surname, age, ACCESS_LEVEL) {
        this->workExperience = workExperience;
        this->subject = subject;
    }
};


#endif //PSS_PROFESSOR_H
