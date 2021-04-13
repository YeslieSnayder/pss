//
// Created by yesliesnayder on 12.04.2021.
//

#ifndef PSS_NOTFOUNDEXCEPTION_H
#define PSS_NOTFOUNDEXCEPTION_H


class NotFoundException : public std::exception{
    string message;
public:
    NotFoundException(string& message) : message(message) {}
    NotFoundException(long int id) : message(to_string(id)) {}

    const string &getMessage() const {
        return message;
    }
};


#endif //PSS_NOTFOUNDEXCEPTION_H
