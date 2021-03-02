//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_PROFESSOR_H
#define PSS_PROFESSOR_H

#include <utility>

#include "User.h"
#include "Student.h"

class Professor : public User {
    int workExperience;
    Laboratory subject;

public:
    static const AccessLevel ACCESS_LEVEL = YELLOW;

    Professor(string name, string surname, int age, Laboratory subject, int workExperience, string extraInfo="")
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)) {
        this->workExperience = workExperience;
        this->subject = subject;
    }

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: Professor"
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + ", laboratory: " + Laboratory_nms::toString(subject)
            + ", work experience (years): " + to_string(workExperience)
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }

    int getWorkExperience() const {
        return workExperience;
    }

    void setWorkExperience(User *user, int workExperience) {
        if (user->getAccessLevel() == SUPER_USER)
            Professor::workExperience = workExperience;
    }

    Laboratory getLaboratory() const {
        return subject;
    }

    void setSubject(User *user, Laboratory subject) {
        if (user->getAccessLevel() == SUPER_USER)
            Professor::subject = subject;
    }
};


#endif //PSS_PROFESSOR_H
