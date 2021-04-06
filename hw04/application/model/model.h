//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_MODEL_H
#define PSS_MODEL_H

#include "../db/database.h"

template<class T>
class Model {
    Database* db;
public:
    Model(Database db) : db(&db) {}

    unsigned long int createPassenger(string data) {

    }
};


#endif //PSS_MODEL_H
