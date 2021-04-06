//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_DATABASE_H
#define PSS_DATABASE_H

using namespace std;

class Database {
public:
    virtual unsigned long int createPassenger(string data) = 0;
    virtual bool isPassengerExists(string data) = 0;
};


#endif //PSS_DATABASE_H
