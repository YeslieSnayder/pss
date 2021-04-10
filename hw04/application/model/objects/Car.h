//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_CAR_H
#define PSS_CAR_H

#include "Address.h"

using namespace std;

enum class CarType {
    Economy,
    Comfort,
    ComfortPlus,
    Business
};

class Car {
    string model;
    CarType carType;
    GEOAddress currentAddress = GEOAddress(0, 0);
    string color;
    unsigned long int number;

public:
    Car() = default;

    bool operator==(const Car& obj) const {
        return model == obj.model && carType == obj.carType && currentAddress == obj.currentAddress
                && color == obj.color && number == obj.number;
    }

    bool operator!=(const Car& obj) const {
        return !(operator==(obj));
    }
};


#endif //PSS_CAR_H
