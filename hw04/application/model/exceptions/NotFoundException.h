//
// Created by yesliesnayder on 12.04.2021.
//

#ifndef PSS_NOTFOUNDEXCEPTION_H
#define PSS_NOTFOUNDEXCEPTION_H

using namespace std;

class NotFoundException : public exception {
    string message;
public:
    NotFoundException(string& message) : message(message) {}
    NotFoundException(long int id) : message(to_string(id)) {}

    string getMessage() const {
        return message;
    }
};


#endif //PSS_NOTFOUNDEXCEPTION_H
