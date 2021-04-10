//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_DATABASE_H
#define PSS_DATABASE_H

#include "../model/objects/Passenger.h"
#include "../model/objects/Driver.h"

using namespace std;

class Database {
public:
    virtual unsigned long int createPassenger(Passenger passenger) = 0;
    virtual Passenger* getPassenger(Passenger passenger) = 0;
};


#endif //PSS_DATABASE_H
