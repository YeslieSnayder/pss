//
// Created by yesliesnayder on 15.04.2021.
//

#ifndef PSS_CSVDATABASE_H
#define PSS_CSVDATABASE_H

#include "../../include/rapidcsv/rapidcsv.h"
#include "database.h"

const string CAR_DB_FILEPATH = "../application/db/db_files/cars.csv";
const string ORDER_DB_FILEPATH = "../application/db/db_files/orders.csv";
const string DRIVER_DB_FILEPATH = "../application/db/db_files/drivers.csv";
const string PASSENGER_DB_FILEPATH = "../application/db/db_files/passengers.csv";

class CSVDatabase : public Database {
public:

    //////////////   DRIVERS   //////////////

    virtual unsigned long int createDriver(Driver& driver) {
        rapidcsv::Document driver_doc(DRIVER_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));
        rapidcsv::Document car_doc(CAR_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));

        driver.setId(driver_doc.GetRowCount() + 1);
        Car* car = driver.getPersonalCar();
        car->setDriverId(driver.getId());

        // Driver data
        unsigned long int id = driver.getId();
        string name = driver.getName();
        double rating = driver.getRating();
        string status;
        if (driver.getStatus() == DriverStatus::NOT_WORKING)
            status = "not_working";
        else if (driver.getStatus() == DriverStatus::WORKING)
            status = "working";
        else if (driver.getStatus() == DriverStatus::IN_RIDE)
            status = "in_ride";
        else
            status = "not_working";

        driver_doc.InsertRow<int>(id);
        driver_doc.SetCell<string>(0, id, name);
        driver_doc.SetCell<int>(1, id, rating);
        driver_doc.SetCell<string>(2, id, status);
        driver_doc.Save();

        // Car data
        string model = car->getModel();
        string color = car->getColor();
        string number = car->getNumber();
        // id
        unsigned int freeBottleOfWater = car->getFreeBottleOfWater();
        string carType;
        if (car->getCarType() == CarType::Economy)
            carType = "economy";
        else

        return driver.getId();
    }

    virtual Driver* getDriver(Driver& driver) {
        rapidcsv::Document doc(DRIVER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        for (int i = 0; i < doc.GetRowCount(); i++) {
            vector<string> obj = doc.GetRow<string>(i);

        }

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

    virtual Car* getCar(unsigned long int driver_id) {
        Driver* driver = getDriver(driver_id);
        if (driver == nullptr)
            return nullptr;
        return driver->getPersonalCar();
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
};


#endif //PSS_CSVDATABASE_H
