//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_DIRECTOR_H
#define PSS_DIRECTOR_H

#include <utility>
#include "User.h"

class Director : public User {
public:
    static const AccessLevel ACCESS_LEVEL = RED;

    Director(string name, string surname, int age) : User(std::move(name), std::move(surname), age, ACCESS_LEVEL) {}

private:
    void change_stipu() {
        // stipa = stipa / 0;
    }
};


#endif //PSS_DIRECTOR_H
