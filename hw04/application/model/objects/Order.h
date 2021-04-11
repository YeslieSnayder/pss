//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_ORDER_H
#define PSS_ORDER_H

#include <ctime>
#include "rapidjson/document.h"

#include "Address.h"
#include "Car.h"

enum class OrderStatus : int {
    READY,
    PROCESSING,
    COMPLETE
};

class Order {
    static const unsigned long int NULL_ID = 0;

    unsigned long int id = NULL_ID;
    GEOAddress startPoint{0,0};
    GEOAddress destination{0,0};
    std::time_t startTime;
    Car* car;
    float price;
    unsigned long int passenger_id;
    unsigned long int driver_id;

    OrderStatus status;

public:
    Order(const GEOAddress &startPoint, const GEOAddress &destination, time_t startTime, unsigned long passengerId,
          unsigned long driverId, const OrderStatus &status, Car &car, float price)
                                      : startPoint(startPoint), destination(destination), startTime(startTime),
                                        passenger_id(passengerId), driver_id(driverId), status(status), car(&car),
                                        price(price) {}

    Order(unsigned long id, const GEOAddress &startPoint, const GEOAddress &destination, time_t startTime,
          unsigned long passengerId, unsigned long driverId, const OrderStatus &status, Car &car, float price)
                                      : id(id), startPoint(startPoint), destination(destination), startTime(startTime),
                                        passenger_id(passengerId), driver_id(driverId), status(status), car(&car),
                                        price(price) {}

    Order(const rapidjson::Document& json) {

    }

    bool operator==(const Order& obj) const {
        return startPoint == obj.startPoint && destination == obj.destination && startTime == obj.startTime
            && passenger_id == obj.passenger_id && driver_id == obj.driver_id;
    }

    bool operator!=(const Order& obj) const {
        return !(operator==(obj));
    }
};


#endif //PSS_ORDER_H
