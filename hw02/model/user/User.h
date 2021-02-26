//
// Created by yesliesnayder on 26.02.2021.
//

#ifndef PSS_USER_H
#define PSS_USER_H

#include "../AccessLevel.h"
#include "../../Logger.h"
#include <string>

using namespace std;

static int ID = 0;

class User {
protected:
    AccessLevel accessLevel;
    string name, surname;
    int age;
    int id;

public:
    User(User &other) {
        this->accessLevel = other.accessLevel;
        this->name = other.name;
        this->surname = other.surname;
        this->age = other.age;
        this->id = other.id;
    }

    User(string name, string surname, int age, AccessLevel accessLevel)
            : name(move(name)), surname(move(surname)), age(age), accessLevel(accessLevel) {
        id = ++ID;
    }

    ~User() = default;

    virtual void printInfo() {
        log("id: " + to_string(id)
            + ", name: " + name + " " + surname
            + ", age: " + to_string(age)
            + ", access level: " + AccessLevel_nms::toString(accessLevel));
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
};

#endif //PSS_USER_H
