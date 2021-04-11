//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_TESTDATABASE_H
#define PSS_TESTDATABASE_H

#include <vector>
#include "database.h"

using namespace std;

class TestDatabase : public Database {
    vector<Passenger> passengers;
    vector<Driver> drivers;

public:
    TestDatabase() = default;

    unsigned long createDriver(Driver driver) {
        driver.setId(drivers.size() + 1);
        drivers.push_back(driver);
        return driver.getId();
    }

    Driver *getDriver(Driver driver) {
        for (auto& d : drivers) {
            if (d == driver)
                return &d;
        }
        return nullptr;
    }

    virtual unsigned long int createPassenger(Passenger passenger) {
        passenger.setId(passengers.size() + 1);
        passengers.push_back(passenger);
        return passenger.getId();
    }

    virtual Passenger* getPassenger(Passenger passenger) {
        for (auto& p : passengers) {
            if (p == passenger)
                return &p;
        }
        return nullptr;
    }
};


#endif //PSS_TESTDATABASE_H
