//
// Created by yesliesnayder on 20.02.2021.
//

#ifndef PSS_ADMIN_H
#define PSS_ADMIN_H

#include "User.h"

class Admin : User {
public:
    Admin() : User("hacker", "mr.robot", SUPER_USER) = default;

    void changeAccess(User& user, AccessLevel newAccess) {
        user.setAccessLevel(*this, newAccess);
    }
};


#endif //PSS_ADMIN_H
