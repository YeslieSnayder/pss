//
// Created by yesliesnayder on 15.04.2021.
//

#ifndef PSS_DATABASEEXCEPTION_H
#define PSS_DATABASEEXCEPTION_H

class DatabaseException : public exception {
    string message;
public:
    DatabaseException(string message) : message(message) {}

    string getMessage() const {
        return message;
    }
};

#endif //PSS_DATABASEEXCEPTION_H
