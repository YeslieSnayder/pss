//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVER_H
#define PSS_DRIVER_H

#include <utility>
#include <vector>
#include "rapidjson/document.h"

#include "Order.h"
#include "Car.h"

using namespace std;

enum class DriverStatus : int {
    NOT_WORKING,
    WORKING,
    IN_RIDE
};

class Driver {
    static const unsigned long int NULL_ID = 0;

    unsigned long int id = NULL_ID;
    string name;
    float rating;   // 0.0 <= value <= 5.0
    vector<Order> orderHistory;
    Car *personalCar;
    DriverStatus status;

public:
    Driver(string name, float rating, const vector<Order> &orderHistory,
                                   Car &personalCar, DriverStatus status) : name(std::move(name)), rating(rating),
                                                                           orderHistory(orderHistory),
                                                                           personalCar(&personalCar),
                                                                           status(status) {}

    Driver(const rapidjson::Document& json) {

    }

    bool operator==(const Driver& obj) const {
        if (name == obj.name && rating == obj.rating && personalCar == obj.personalCar && status == obj.status
                && orderHistory.size() == obj.orderHistory.size()) {
            for (int i = 0; i < orderHistory.size(); i++) {
                if (orderHistory[i] != obj.orderHistory[i])
                    return false;
            }
            return true;
        }
        return false;
    }

    bool operator!=(const Driver& obj) const {
        return !(operator==(obj));
    }
};


#endif //PSS_DRIVER_H
