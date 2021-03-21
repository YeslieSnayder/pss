//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_LABEMPLOYEE_H
#define PSS_LABEMPLOYEE_H

#include <utility>

#include "User.h"
#include "../Laboratory.h"
#include "../../Logger.h"

class LabEmployee : public User {
    bool _isPhd;
    Laboratory lab;

public:
    static const inline string TYPE = "Lab employee";
    static const AccessLevel ACCESS_LEVEL = GREEN;

    LabEmployee(string name, string surname, int age, Laboratory laboratory, bool isPhd, string extraInfo="")
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, extraInfo) {
        this->_isPhd = isPhd;
        this->lab = laboratory;
        this->extraInfo = std::move(extraInfo);
    }

    void printInfo() {
        log("id: " + to_string(id)
            + ", status: " + TYPE
            + ", name: " + User::getName()
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + ", laboratory: " + Laboratory_nms::toString(lab)
            + ((_isPhd) ? ", Phd" : "")
            + ((extraInfo.empty()) ? "" : ", extra: " + extraInfo));
    }

    bool isPhd() const {
        return _isPhd;
    }

    void setIsPhd(User *user, bool isPhd) {
        if (user->getAccessLevel() == SUPER_USER || user->getId() == this->id)
            LabEmployee::_isPhd = isPhd;
    }

    Laboratory getLaboratory() const {
        return this->lab;
    }

    void setLab(User *user, Laboratory lab) {
        if (user->getAccessLevel() == SUPER_USER || user->getId() == this->id)
            LabEmployee::lab = lab;
    }
};


#endif //PSS_LABEMPLOYEE_H
