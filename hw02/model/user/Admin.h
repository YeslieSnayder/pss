//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_ADMIN_H
#define PSS_ADMIN_H

#include <utility>

#include "User.h"

class Admin : public User {
public:
    static const AccessLevel ACCESS_LEVEL = SUPER_USER;

    Admin(string name, string surname, int age, string extraInfo="")
        : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)) { }

    void changeAccess(User& user, AccessLevel newAccess) {
        user.setAccessLevel(*this, newAccess);
    }

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: Admin"
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }
};


#endif //PSS_ADMIN_H
