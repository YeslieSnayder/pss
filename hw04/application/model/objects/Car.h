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
    GEOAddress currentAddress;
    string color;
    int number;

public:
    Car() = default;
};


#endif //PSS_CAR_H
