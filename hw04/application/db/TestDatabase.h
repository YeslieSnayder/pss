//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_TESTDATABASE_H
#define PSS_TESTDATABASE_H


class TestDatabase : public Database {
    unsigned long int createPassenger(string data) {
        return 0;
    }

    bool isPassengerExists(string data) {
        return false;
    }
};


#endif //PSS_TESTDATABASE_H
