//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_GUEST_H
#define PSS_GUEST_H

#include <utility>

#include "User.h"

class Guest : public User {
    string hometown;
    uint8_t groupNumber;
public:
    static const inline string TYPE = "Guest";
    static const AccessLevel ACCESS_LEVEL = BLUE;

    Guest(string name, string surname, int age, string hometown, uint8_t groupNumber, string extraInfo="")
    : User(std::move(name), std::move(surname), age, ACCESS_LEVEL, std::move(extraInfo)),
            hometown(std::move(hometown)), groupNumber(groupNumber) { }

    const string &getHometown() const {
        return hometown;
    }

    void setHometown(User *user, const string &hometown) {
        if (user->getAccessLevel() == SUPER_USER || user->getId() == this->id)
            Guest::hometown = hometown;
    }

    uint8_t getGroupNumber() const {
        return groupNumber;
    }

    void setGroupNumber(User *user, uint8_t groupNumber) {
        if (user->getAccessLevel() == SUPER_USER || user->getId() == this->id)
            Guest::groupNumber = groupNumber;
    }

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: " + TYPE
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + ", group number: " + to_string(groupNumber)
            + ", hometown: " + hometown
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }
};


#endif //PSS_GUEST_H
