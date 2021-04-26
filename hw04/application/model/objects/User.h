//
// Created by yesliesnayder on 16.04.2021.
//

#ifndef PSS_USER_H
#define PSS_USER_H


class User {
protected:
    unsigned long int id{};
    std::string name{};

public:
    static const unsigned long int NULL_ID = 0;

    unsigned long getId() const {
        return id;
    }

    const std::string &getName() const {
        return name;
    }

    void setId(unsigned long id) {
        User::id = id;
    }

    void setName(const std::string &name) {
        User::name = name;
    }
};


#endif //PSS_USER_H
