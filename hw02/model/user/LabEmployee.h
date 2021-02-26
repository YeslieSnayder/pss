//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_LABEMPLOYEE_H
#define PSS_LABEMPLOYEE_H

#include <utility>

#include "User.h"
#include "../Laboratory.h"
#include "../../Logger.h"

class LabEmployee : public User {
    bool isPhd;
    Laboratory lab;
    string extraInfo;

public:
    static const AccessLevel ACCESS_LEVEL = GREEN;

    LabEmployee(string name, string surname, int age, Laboratory laboratory, bool isPhd, string extraInfo="")
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL) {
        this->isPhd = isPhd;
        this->lab = laboratory;
        this->extraInfo = std::move(extraInfo);
    }

    virtual Laboratory getLaboratory() const {
        return this->lab;
    }

    void printInfo() {
        log("id: " + to_string(id)
            + ", name: " + User::getName()
            + ", age: " + to_string(age)
            + ((isPhd) ? ", Phd" : "")
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + ", laboratory: " + Laboratory_nms::toString(lab)
            + ((extraInfo.empty()) ? "" : ", extra: " + extraInfo));
    }
};


#endif //PSS_LABEMPLOYEE_H
