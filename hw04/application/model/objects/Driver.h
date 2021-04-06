//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVER_H
#define PSS_DRIVER_H

#include <vector>
#include "Order.h"
#include "Car.h"

using namespace std;

enum class DriverStatus : int {
    NOT_WORKING,
    WORKING,
    IN_RIDE
};

class Driver {
    string name;
    float rating;
    vector<Order> orderHistory;
    Car personalCar;
    DriverStatus status;

public:
    Driver() = default;
};


#endif //PSS_DRIVER_H
