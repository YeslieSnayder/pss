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
    vector<Car> cars;

public:

    //////////////   DRIVERS   //////////////

    virtual unsigned long int createDriver(Driver& driver) {
        driver.setId(drivers.size() + 1);
        drivers.push_back(driver);
        for (Car car : driver.getPersonalCars()) {
            car.setDriverId(driver.getId());
            cars.push_back(car);
        }
        return driver.getId();
    }

    virtual Driver* getDriver(Driver& driver) {
        for (auto& d : drivers) {
            if (d == driver) {
                vector<Car> driver_cars = getCars(d.getId());
                d.setPersonalCars(driver_cars);
                return &d;
            }
        }
        return nullptr;
    }

    virtual Driver* getDriver(unsigned long int driver_id) {
        for (auto& d : drivers) {
            if (d.getId() == driver_id) {
                vector<Car> driver_cars = getCars(d.getId());
                d.setPersonalCars(driver_cars);
                return &d;
            }
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

    /////////////   PASSENGERS   /////////////

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

    virtual vector<Car> getCars(unsigned long int driver_id) {
        vector<Car> res;
        for (Car &car : cars) {
            if (car.getDriverId() == driver_id)
                res.push_back(car);
        }
        return res;
    }

    virtual Order* createOrder(Order& order) {
        order.setId(orders.size() + 1);
        orders.push_back(order);
        return &order;
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

    virtual Order* getOrder(unsigned long int order_id) {
        for (Order& order : orders) {
            if (order.getId() == order_id)
                return &order;
        }
        return nullptr;
    }

    virtual Order* getLastOrder(unsigned long int id, ObjectType type) {
        vector<Order> prevOrders = getOrderHistory(id, type);
        if (prevOrders.empty())
            return nullptr;
        int max_id = 0, index;
        for (int i = 0; i < prevOrders.size(); i++) {
            if (prevOrders[i].getId() > max_id) {
                max_id = prevOrders[i].getId();
                index = i;
            }
        }
        return &prevOrders[index];
    }

    virtual Car* getCar(string number) {
        for (Car& car : cars) {
            if (car.getNumber() == number)
                return &car;
        }
        return nullptr;
    }


    virtual vector<Driver> getAllDrivers() { return vector<Driver>(); }
    virtual vector<Passenger> getAllPassengers() { return vector<Passenger>(); }
    virtual vector<Car> getAllCars() { return vector<Car>(); }
    virtual vector<Order> getAllOrders() { return vector<Order>(); }
    virtual unsigned long int createAdmin(Admin& admin) { return 0; }
    virtual Admin* patchAdmin(unsigned long int id, Admin& admin) { return nullptr; }
    virtual Admin* getAdmin(string email) { return nullptr; }
    virtual Admin* getAdmin(unsigned long int id) { return nullptr; }
    virtual vector<Admin> getAllAdmins() { return vector<Admin>(); }
};


#endif //PSS_TESTDATABASE_H
