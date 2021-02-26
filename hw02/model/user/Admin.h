//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_ADMIN_H
#define PSS_ADMIN_H

#include <utility>

#include "User.h"

class Admin : public User {
public:
    static const AccessLevel ACCESS_LEVEL = SUPER_USER;

    Admin(string name, string surname, int age) : User(std::move(name), std::move(surname), age, ACCESS_LEVEL) { }

    void changeAccess(User& user, AccessLevel newAccess) {
        user.setAccessLevel(*this, newAccess);
    }
};


#endif //PSS_ADMIN_H
