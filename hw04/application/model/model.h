//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_MODEL_H
#define PSS_MODEL_H

#include "rapidjson/document.h"
#include "../db/database.h"

#include "objects/Passenger.h"
#include "../db/database.h"
#include "../db/TestDatabase.h"

using namespace rapidjson;

class Model {
    static inline Database* db;

public:
    Model(Database* _db) {
        Model::db = _db;
    }

    static unsigned long int createPassenger(Document& data) {
        Passenger* passenger = findPassenger(data);
        if (passenger != nullptr)
            return passenger->getId();

        passenger = new Passenger(data);
        return Model::db->createPassenger(*passenger);
    }

    static Passenger* findPassenger(Document& data) {
        Passenger passenger(data);
        return Model::db->getPassenger(passenger);
    }
};


#endif //PSS_MODEL_H
