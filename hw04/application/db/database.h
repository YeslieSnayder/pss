//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_DATABASE_H
#define PSS_DATABASE_H

#include <vector>

#include "../model/objects/Passenger.h"
#include "../model/objects/Driver.h"
#include "../model/objects/Admin.h"

using namespace std;

enum class ObjectType {
    DRIVER, PASSENGER
};

class Database {
public:

    ////////////     Driver     ////////////

    virtual unsigned long int createDriver(Driver& driver) = 0;
    virtual Driver* getDriver(Driver& driver) = 0;
    virtual Driver* getDriver(unsigned long int driver_id) = 0;
    virtual Driver* patchDriver(Driver& driver) = 0;
    virtual vector<Order> getAvailableOrders() = 0;
    virtual vector<Driver> getAllDrivers() = 0;

    ///////////     Passenger     ///////////

    virtual unsigned long int createPassenger(Passenger& passenger) = 0;
    virtual Passenger* getPassenger(Passenger& passenger) = 0;
    virtual Passenger* getPassenger(unsigned long int passenger_id) = 0;
    virtual Passenger* patchPassenger(Passenger& passenger) = 0;
    virtual vector<Order> getOrderHistory(unsigned long int id, ObjectType type) = 0;
    virtual vector<Passenger> getAllPassengers() = 0;

    //////////////     Car     //////////////

    virtual vector<Car> getCars(unsigned long int driver_id) = 0;
    virtual Car* getCar(string number) = 0;
    virtual vector<Car> getAllCars() = 0;

    /////////////     Order     /////////////

    virtual Order* createOrder(Order& order) = 0;
    virtual Order* changeOrder(Order& order) = 0;
    virtual Order* getOrder(unsigned long int order_id) = 0;
    virtual Order* getLastOrder(unsigned long int id, ObjectType type) = 0;
    virtual vector<Order> getAllOrders() = 0;

    /////////////     Admin     /////////////

    virtual unsigned long int createAdmin(Admin& admin) = 0;
    virtual Admin* patchAdmin(unsigned long int id, Admin& admin) = 0;
    virtual Admin* getAdmin(string email) = 0;
    virtual Admin* getAdmin(unsigned long int id) = 0;
    virtual vector<Admin> getAllAdmins() = 0;
};


#endif //PSS_DATABASE_H
