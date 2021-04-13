//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_MODEL_H
#define PSS_MODEL_H

#include "rapidjson/document.h"

#include "exceptions/IncorrectDataException.h"
#include "exceptions/NotFoundException.h"
#include "objects/Passenger.h"
#include "../db/database.h"
#include "../db/TestDatabase.h"

using namespace rapidjson;

class Model {
    static inline Database* db;

public:
    ~Model() = default;
    Model(Database* _db) {
        Model::db = _db;
    }

    static unsigned long int createDriver(Document& data) {
        Driver* driver = findDriver(data);
        if (driver != nullptr)
            return driver->getId();

        driver = new Driver(data);
        return Model::db->createDriver(*driver);
    }

    static Driver* findDriver(Document& data) {
        Driver driver(data);
        return Model::db->getDriver(driver);
    }

    static Driver* getDriver(unsigned long int driver_id) {
        if (driver_id <= 0)
            throw NotFoundException(driver_id);
        return Model::db->getDriver(driver_id);
    }

    static Driver* patchDriver(unsigned long int driver_id, Document& data) {
        Driver* driver = getDriver(driver_id);
        if (driver == nullptr)
            throw NotFoundException(driver_id);
        driver->patch(data);
        return Model::db->patchDriver(*driver);
    }

    static vector<Order> getDriverOrderHistory(unsigned long int driver_id) {
        if (driver_id <= 0)
            throw NotFoundException(driver_id);
        return Model::db->getOrderHistory(driver_id, ObjectType::DRIVER);
    }

    static Car* getCar(unsigned long int driver_id) {
        if (driver_id <= 0)
            throw NotFoundException(driver_id);
        return Model::db->getCar(driver_id);
    }

    static vector<Order> getAvailableOrders() {
        return Model::db->getAvailableOrders();
    }

    static Order* acceptOrderByDriver(unsigned long int driver_id, unsigned long int order_id) {
        Car* car = getCar(driver_id);
        Order* order = Model::db->getOrder(order_id);
        order->setCar(car);
        order->setDriverId(driver_id);
        order->setStatus(OrderStatus::PROCESSING);
        return Model::db->changeOrder(*order);
    }

    static unsigned long int completeOrder(Document& data) {
        IncorrectDataException exc;
        if (!data.HasMember("order_id"))
            exc.addEntry("order_id", "Order: Body does not have parameter 'order_id'");
        else if (!data["order_id"].IsNumber())
            exc.addEntry("order_id", "Order: Parameter 'order_id' is incorrect, expected type: 'positive integer'");

        if (!data.HasMember("complete_time"))
            exc.addEntry("complete_time", "Order: Body does not have parameter 'complete_time'");
        else if (!data["complete_time"].IsString())
            exc.addEntry("complete_time", "Order: Parameter 'complete_time' is incorrect, expected type: 'string'");

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());

        unsigned long int order_id = data["order_id"].GetInt64();
        string time = data["complete_time"].GetString();
        Order* order = Model::db->getOrder(order_id);
        if (order == nullptr)
            throw NotFoundException(order_id);

        order->setStatus(OrderStatus::COMPLETE);
        return order_id;
    }



    static unsigned long int createPassenger(Document& data) {
        Passenger* passenger = getPassenger(data);
        if (passenger != nullptr)
            return passenger->getId();

        passenger = new Passenger(data);
        return Model::db->createPassenger(*passenger);
    }

    static Passenger* getPassenger(Document& data) {
        Passenger passenger(data);
        return Model::db->getPassenger(passenger);
    }

    static Passenger* patchPassenger(unsigned long int passenger_id, Document& data) {
        Passenger* passenger = getPassenger(data);
        if (passenger == nullptr)
            throw NotFoundException(passenger_id);
        passenger->patch(data);
        return Model::db->patchPassenger(*passenger);
    }

    static PreOrder* assignOrder(unsigned long int passenger_id, Document& data) {
        return new PreOrder(data);
    }

    static Order* assignAndOrderRide(unsigned long int passenger_id, Document& data) {
        Order* order = new Order(data, passenger_id);
        Model::db->createOrder(order);
    }

    static Order* getLastOrder(unsigned long int passenger_id) {

    }

    static vector<Order> getPassengerOrderHistory(unsigned long int passenger_id) {
        getDriver(passenger_id);
        return Model::db->getOrderHistory(passenger_id, ObjectType::PASSENGER);
    }
};


#endif //PSS_MODEL_H
