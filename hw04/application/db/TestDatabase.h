//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_TESTDATABASE_H
#define PSS_TESTDATABASE_H

#include <vector>
#include "database.h"

using namespace std;

class TestDatabase : public Database {
    vector<Passenger> passengers;
    vector<Driver> drivers;
    vector<Order> orders;

public:
    virtual unsigned long int createDriver(Driver& driver) {
        driver.setId(drivers.size() + 1);
        drivers.push_back(driver);
        return driver.getId();
    }

    virtual Driver* getDriver(Driver& driver) {
        for (auto& d : drivers) {
            if (d == driver)
                return &d;
        }
        return nullptr;
    }

    virtual Driver* getDriver(unsigned long int driver_id) {
        for (auto& d : drivers) {
            if (d.getId() == driver_id)
                return &d;
        }
        return nullptr;
    }

    virtual Driver* patchDriver(Driver& driver) {
        for (auto& d : drivers) {
            if (d.getId() == driver.getId())
                d = driver;
                return &d;
        }
        return nullptr;
    }

    virtual vector<Order> getAvailableOrders() {
        vector<Order> list;
        for (Order order : orders) {
            if (order.getStatus() == OrderStatus::READY)
                list.push_back(order);
        }
        return list;
    }



    virtual unsigned long int createPassenger(Passenger& passenger) {
        passenger.setId(passengers.size() + 1);
        passengers.push_back(passenger);
        return passenger.getId();
    }

    virtual Passenger* getPassenger(Passenger& passenger) {
        for (auto& p : passengers) {
            if (p == passenger)
                return &p;
        }
        return nullptr;
    }

    virtual Passenger* getPassenger(unsigned long int passenger_id) {
        for (auto& p : passengers) {
            if (p.getId() == passenger_id)
                return &p;
        }
        return nullptr;
    }

    virtual Passenger* patchPassenger(Passenger& passenger) {
        for (auto& p : passengers) {
            if (p.getId() == passenger.getId())
                p = passenger;
                return &p;
        }
        return nullptr;
    }

    virtual vector<Order> getOrderHistory(unsigned long int id, ObjectType type) {
        vector<Order> history;
        for (Order order : orders) {
            if (order.getDriverId() == id && type == ObjectType::DRIVER ||
                    order.getPassengerId() == id && type == ObjectType::PASSENGER)
                history.push_back(order);
        }
        return history;
    }

    virtual Car* getCar(unsigned long int driver_id) {
        Driver* driver = getDriver(driver_id);
        if (driver == nullptr)
            return nullptr;
        return driver->getPersonalCar();
    }

    virtual Order* getOrder(unsigned long int order_id) {
        for (Order& order : orders) {
            if (order.getId() == order_id)
                return &order;
        }
        return nullptr;
    }

    virtual Order* changeOrder(Order& order) {
        for (Order& o : orders) {
            if (o.getId() == order.getId()) {
                o = order;
                return &o;
            }
        }
        return nullptr;
    }
};


#endif //PSS_TESTDATABASE_H
