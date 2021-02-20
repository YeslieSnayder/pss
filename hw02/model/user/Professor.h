//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_PROFESSOR_H
#define PSS_PROFESSOR_H

#include "User.h"
#include "Student.h"

class Professor : public User {
    int workExperience;
    Student teacherPet[];
    string subject;

public:
    Professor(string name, string surname, int age, string subject, int workExperience, Student &teacherPet[])
            : User(std::move(name), std::move(surname), age, YELLOW) {
        this->workExperience = workExperience;
        this->teacherPet = teacherPet;
        this->subject = std::move(subject);
    }

    Professor(const string& name, const string& surname, int age, const string& subject, int workExperience)
            : Professor(name, surname, age, subject, workExperience, Student[0]) { }
};


#endif //PSS_PROFESSOR_H
