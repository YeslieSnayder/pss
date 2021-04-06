//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_MODEL_H
#define PSS_MODEL_H

#include "../db/database.h"

class Model {
    Database* db;
public:
    Model(Database* db) : db(db) {}

    static unsigned long int createPassenger(string data) {
        return 0;
    }
};


#endif //PSS_MODEL_H
