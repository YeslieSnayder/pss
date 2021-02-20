//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_LABEMPLOYEE_H
#define PSS_LABEMPLOYEE_H

#include <utility>

#include "User.h"

class LabEmployee : public User {
    bool isPhd;
    string subject;

public:
    LabEmployee(string name, string surname, int age, string subject, bool isPhd) : User(std::move(name), std::move(surname), age, GREEN) {
        this->isPhd = isPhd;
        this->subject = std::move(subject);
    }
};


#endif //PSS_LABEMPLOYEE_H
