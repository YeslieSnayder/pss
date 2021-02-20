//
// Created by Andrey Kuzmickiy on 20.02.2021.
//

#ifndef PSS_USER_H
#define PSS_USER_H

#include "../AccessLevel.h"
#include "../room/Room.h"
#include <string>

using namespace std;

class User {
    AccessLevel accessLevel;
    string name, surname;
    int age;

public:
    User(string name, string surname, int age, AccessLevel accessLevel)
        : name(move(name)), surname(move(surname)), age(age), accessLevel(accessLevel) { }

    ~User() { }

    AccessLevel getAccessLevel() const {
        return accessLevel;
    }

    const string getName() const {
        return name + " " + surname;
    }

    int getAge() const {
        return age;
    }

    void setAccessLevel(User &user, AccessLevel accessLevel) {
        if (user.accessLevel == SUPER_USER)
            User::accessLevel = accessLevel;
    }

    void setName(User &user, const string &name) {
        if (user.accessLevel == SUPER_USER)
            User::name = name;
    }

    void setSurname(User &user, const string &surname) {
        if (user.accessLevel == SUPER_USER)
            User::surname = surname;
    }

    void setAge(User &user, int age) {
        if (user.accessLevel == SUPER_USER)
            User::age = age;
    }
};


#endif //PSS_USER_H
