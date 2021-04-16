//
// Created by yesliesnayder on 16.04.2021.
//

#ifndef PSS_FORBIDDENEXCEPTION_H
#define PSS_FORBIDDENEXCEPTION_H

#include "../../db/database.h"

class ForbiddenException : public std::exception {
    string message;

public:
    ForbiddenException(unsigned long int id, ObjectType type) {
        if (type == ObjectType::PASSENGER)
            message = "Passenger (id = " + to_string(id) + ") has tried to give access to method that (s)he does not have access!";
        else if (type == ObjectType::DRIVER)
            message = "Driver (id = " + to_string(id) + ") has tried to give access to method that (s)he does not have access!";
        else
            message = "User (id = " + to_string(id) + ") has tried to give access to method that (s)he does not have access!";
    }

    const string &getMessage() const {
        return message;
    }
};

#endif //PSS_FORBIDDENEXCEPTION_H
