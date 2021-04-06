//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_ORDER_H
#define PSS_ORDER_H

#include <ctime>
#include "Address.h"

class Order {
public:
    unsigned long int id;
    GEOAddress startPoint;
    GEOAddress destination;
    std::time_t startTime;
    unsigned long int passenger_id;
    unsigned long int driver_id;

    Order(const GEOAddress &startPoint, const GEOAddress &destination, time_t startTime, unsigned long passengerId,
          unsigned long driverId) : startPoint(startPoint), destination(destination), startTime(startTime),
                                    passenger_id(passengerId), driver_id(driverId) {}

    Order(unsigned long id, const GEOAddress &startPoint, const GEOAddress &destination, time_t startTime,
          unsigned long passengerId, unsigned long driverId) : id(id), startPoint(startPoint), destination(destination),
                                                               startTime(startTime), passenger_id(passengerId),
                                                               driver_id(driverId) {}
};


#endif //PSS_ORDER_H
