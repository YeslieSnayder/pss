//
// Created by yesliesnayder on 16.04.2021.
//

#ifndef PSS_ADMIN_H
#define PSS_ADMIN_H

#include "User.h"

class Admin : public User {
    string password;

public:
    Admin(unsigned long id, string& name, string& password) : password(password) {
        Admin::id = id;
        Admin::name = std::move(name);
    }

    bool operator==(const Admin& other) {
        return id == other.id && name == other.name && password == other.password;
    }
};


#endif //PSS_ADMIN_H
