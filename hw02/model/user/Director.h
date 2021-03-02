//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_DIRECTOR_H
#define PSS_DIRECTOR_H

#include <utility>
#include "User.h"

class Director : public User {
public:
    static const AccessLevel ACCESS_LEVEL = RED;

    Director(string name, string surname, int age, string extraInfo="")
        : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)) {}

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: Director"
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }

private:
    void change_stipu() {
        // stipa = stipa / 0;
    }
};


#endif //PSS_DIRECTOR_H
