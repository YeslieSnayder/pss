//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_CAR_H
#define PSS_CAR_H

#include "Address.h"
#include "rapidjson/document.h"

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
    GEOAddress currentAddress{0, 0};
    string color;
    unsigned long int number;
    unsigned long int driver_id;
    unsigned int freeBottleOfWater;

public:
    Car(const string &model, CarType carType, const GEOAddress &currentAddress, const string &color,
        unsigned long number, unsigned long driverId, unsigned int freeBottleOfWater) : model(model), carType(carType),
                                currentAddress(currentAddress), color(color), number(number), driver_id(driverId) {}

    Car(const rapidjson::Document& json) {

    }

    bool operator==(const Car& obj) const {
        return model == obj.model && carType == obj.carType && currentAddress == obj.currentAddress
                && color == obj.color && number == obj.number;
    }

    bool operator!=(const Car& obj) const {
        return !(operator==(obj));
    }
};


#endif //PSS_CAR_H
