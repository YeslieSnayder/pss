//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_ADMIN_H
#define PSS_ADMIN_H

#include <utility>

#include "User.h"
#include "../room/Room.h"

class Admin : public User {
    string password;
public:
    static const inline string TYPE = "Admin";
    static const AccessLevel ACCESS_LEVEL = SUPER_USER;

    Admin(string password) : User(NULL_USER), password(password) {
        accessLevel = ACCESS_LEVEL;
        id = ID++;
    }

    Admin(string name, string surname, int age, string extraInfo="")
        : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)) { }

    Admin(string name, string surname, int age, string extraInfo="", string password="password")
            : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)), password(password) { }

    void changeAccessLevel(User& user, AccessLevel newAccess) {
        user.setAccessLevel(*this, newAccess);
    }

    void giveAccess(User& user, Room& room) {
        room.addAcceptableUser(*this, user);
    }

    const string &getPassword() const {
        return password;
    }

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: " + TYPE
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }
};


#endif //PSS_ADMIN_H
