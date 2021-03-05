//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_USER_H
#define PSS_USER_H

#include "../AccessLevel.h"
#include "../../Logger.h"
#include <utility>

using namespace std;

static int ID = -1;

class User {
protected:
    AccessLevel accessLevel;
    string name, surname;
    string extraInfo;
    uint age;
    uint id;

public:
    static const inline string TYPE = "User";

    User(string name, string surname, int age, AccessLevel accessLevel, string extraInfo="")
            : name(move(name)), surname(move(surname)), age(age),
                accessLevel(accessLevel), extraInfo(std::move(extraInfo)) {
        id = ++ID;
    }

    User(User &other) {
        this->accessLevel = other.accessLevel;
        this->name = other.name;
        this->surname = other.surname;
        this->age = other.age;
        this->id = other.id;
    }

    User(const User &other) {
        this->accessLevel = other.accessLevel;
        this->name = other.name;
        this->surname = other.surname;
        this->age = other.age;
        this->id = other.id;
    }

    ~User() = default;

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", status: " + TYPE
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel)
            + (extraInfo.empty() ? "" : ", extra info: " + extraInfo));
    }

    virtual int getId() const {
        return id;
    }

    virtual AccessLevel getAccessLevel() const {
        return accessLevel;
    }

    virtual const string getName() const {
        return name + " " + surname;
    }

    virtual int getAge() const {
        return age;
    }

    virtual const string getExtraInfo() const {
        return extraInfo;
    }

    virtual void setId(User &user, int id) {
        if (user.accessLevel == SUPER_USER)
            this->id = id;
    }

    virtual void setAccessLevel(User &user, AccessLevel &accessLevel) {
        if (user.accessLevel == SUPER_USER)
            this->accessLevel = accessLevel;
    }

    virtual void setName(User &user, const string &name) {
        if (user.accessLevel == SUPER_USER)
            this->name = name;
    }

    virtual void setSurname(User &user, const string &surname) {
        if (user.accessLevel == SUPER_USER)
            this->surname = surname;
    }

    virtual void setAge(User &user, int age) {
        if (user.accessLevel == SUPER_USER)
            this->age = age;
    }

    virtual void setExtraInfo(User &user, string extraInfo) {
        if (user.accessLevel == SUPER_USER)
            this->extraInfo = extraInfo;
    }
};

const static User NULL_USER("", "", 0, NO_LEVEL);

#endif //PSS_USER_H