//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_MODEL_H
#define PSS_MODEL_H

#include "rapidjson/document.h"

#include "AdminService.h"
#include "exceptions/IncorrectDataException.h"
#include "exceptions/ForbiddenException.h"
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

    //////////////   DRIVERS   //////////////

    static unsigned long int createDriver(Document& data) {
        auto* driver = new Driver(data);
        driver = Model::db->getDriver(*driver);
        if (driver != nullptr)
            return driver->getId();

        driver = new Driver(data);
        unsigned long int id = Model::db->createDriver(*driver);
        bool is_allowed;
        try {
            is_allowed = AdminService::is_driver_function_allowed(id, DriverFunction::LOGIN);
        } catch (NotFoundException e) {
            is_allowed = true;
        }
        if (!is_allowed)
            throw ForbiddenException(id, ObjectType::DRIVER);
        AdminService::allow_driver_all(id);
        return id;
    }

    static Driver* getDriver(unsigned long int driver_id) {
        if (driver_id <= 0)
            throw NotFoundException(driver_id);
        if (AdminService::is_driver_function_allowed(driver_id, DriverFunction::GET))
            return Model::db->getDriver(driver_id);
        else
            throw ForbiddenException(driver_id, ObjectType::DRIVER);
    }

    static Driver* patchDriver(unsigned long int driver_id, Document& data) {
        Driver* driver = getDriver(driver_id);
        if (driver == nullptr)
            throw NotFoundException(driver_id);
        if (AdminService::is_driver_function_allowed(driver_id, DriverFunction::PATCH)) {
            driver->patch(data);
            return Model::db->patchDriver(*driver);
        } else
            throw ForbiddenException(driver_id, ObjectType::DRIVER);
    }

    static vector<Order> getDriverOrderHistory(unsigned long int driver_id) {
        if (driver_id <= 0)
            throw NotFoundException(driver_id);
        if (AdminService::is_driver_function_allowed(driver_id, DriverFunction::GET_ORDER_HISTORY))
            return Model::db->getOrderHistory(driver_id, ObjectType::DRIVER);
        else
            throw ForbiddenException(driver_id, ObjectType::DRIVER);
    }

    static vector<Car> getCars(unsigned long int driver_id) {
        if (driver_id <= 0)
            throw NotFoundException(driver_id);
        if (!AdminService::is_driver_function_allowed(driver_id, DriverFunction::GET_CAR))
            throw ForbiddenException(driver_id, ObjectType::DRIVER);
        return Model::db->getCars(driver_id);
    }

    static vector<Order> getAvailableOrders() {
        return Model::db->getAvailableOrders();
    }

    static Order* acceptOrderByDriver(unsigned long int driver_id, Document& data) {
        IncorrectDataException exc;
        if (!data.HasMember("order_id"))
            exc.addEntry("order_id", "Order: Body does not have parameter 'order_id'");
        else if (!data["order_id"].IsNumber())
            exc.addEntry("order_id", "Order: Parameter 'order_id' is incorrect, expected type: 'positive integer'");
        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());

        unsigned long int order_id = data["order_id"].GetInt64();
        if (!AdminService::is_driver_function_allowed(driver_id, DriverFunction::ACCEPT_ORDER))
            throw ForbiddenException(driver_id, ObjectType::DRIVER);

        srand(time(0));
        Car* car = nullptr;
        {
            vector<Car> cars = getCars(driver_id);
            car = &cars[rand() % cars.size()];
        }
        Driver* driver = getDriver(driver_id);
        Order* order = Model::db->getOrder(order_id);
        if (order->getStatus() != OrderStatus::READY) {
            exc.addEntry("order", "Order: The order have already been assigned");
            throw IncorrectDataException(exc.getErrors());
        }

        order->setCar(car);
        order->setDriverId(driver_id);
        order->setStatus(OrderStatus::PROCESSING);

        vector<Order> orders = driver->getOrderHistory();
        orders.push_back(*order);
        driver->setOrderHistory(orders);
        Model::db->patchDriver(*driver);

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

    /////////////   PASSENGERS   /////////////

    static unsigned long int createPassenger(Document& data) {
        auto* passenger = new Passenger(data);
        passenger = Model::db->getPassenger(*passenger);
        if (passenger != nullptr)
            return passenger->getId();

        passenger = new Passenger(data);
        unsigned long int id = Model::db->createPassenger(*passenger);
        bool is_allowed;
        try {
            is_allowed = AdminService::is_passenger_function_allowed(id, PassengerFunction::LOGIN);
        } catch (NotFoundException e) {
            is_allowed = true;
        }
        if (!is_allowed)
            throw ForbiddenException(id, ObjectType::PASSENGER);
        AdminService::allow_passenger_all(id);
        return id;
    }

    static Passenger* getPassenger(unsigned long int passenger_id) {
        if (passenger_id <= 0)
            throw NotFoundException(passenger_id);
        if (!AdminService::is_passenger_function_allowed(passenger_id, PassengerFunction::GET))
            throw ForbiddenException(passenger_id, ObjectType::PASSENGER);
        return Model::db->getPassenger(passenger_id);
    }

    static Passenger* patchPassenger(unsigned long int passenger_id, Document& data) {
        Passenger* passenger = getPassenger(passenger_id);
        if (passenger == nullptr)
            throw NotFoundException(passenger_id);
        if (!AdminService::is_passenger_function_allowed(passenger_id, PassengerFunction::PATCH))
            throw ForbiddenException(passenger_id, ObjectType::PASSENGER);
        passenger->patch(data);
        return Model::db->patchPassenger(*passenger);
    }

    static PreOrder* assignOrder(unsigned long int passenger_id, Document& data) {
        return new PreOrder(data);
    }

    static Order* assignAndOrderRide(unsigned long int passenger_id, Document& data) {
        Order* order = new Order(passenger_id, data);
        Passenger* passenger = Model::db->getPassenger(passenger_id);
        if (passenger == nullptr)
            throw NotFoundException(passenger_id);
        if (!AdminService::is_passenger_function_allowed(passenger_id, PassengerFunction::ASSIGN_RIDE))
            throw ForbiddenException(passenger_id, ObjectType::PASSENGER);

        vector<Order> orderHistory = passenger->getOrderHistory();
        orderHistory.push_back(*order);
        Model::db->patchPassenger(*passenger);
        return Model::db->createOrder(*order);
    }

    static Order* getLastOrder(unsigned long int passenger_id) {
        Order* order = Model::db->getLastOrder(passenger_id, ObjectType::PASSENGER);
        if (order == nullptr)
            throw NotFoundException(passenger_id);
        return order;
    }

    static vector<Order> getPassengerOrderHistory(unsigned long int passenger_id) {
        if (!AdminService::is_passenger_function_allowed(passenger_id, PassengerFunction::GET_ORDER_HISTORY))
            throw ForbiddenException(passenger_id, ObjectType::PASSENGER);
        getDriver(passenger_id);
        return Model::db->getOrderHistory(passenger_id, ObjectType::PASSENGER);
    }

    static Car* getCarForPassenger(unsigned long int passenger_id, Document& data) {
        if (passenger_id <= 0)
            throw NotFoundException(passenger_id);
        if (!AdminService::is_passenger_function_allowed(passenger_id, PassengerFunction::GET_CAR))
            throw ForbiddenException(passenger_id, ObjectType::PASSENGER);

        IncorrectDataException exc;
        if (!data.HasMember("car_number"))
            exc.addEntry("car_number", "Car: Body does not have parameter 'car_number'");
        else if (data["car_number"].IsString())
            exc.addEntry("car_number", "Car: Parameter 'car_number' is incorrect, expected type: 'string'");
        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());

        string number = data["car_number"].GetString();
        Car* car = Model::db->getCar(number);
        if (car == nullptr)
            throw NotFoundException(number);

        return car;
    }

    static Order* createOrder(Document& data) {
        Order order(data);
        return Model::db->createOrder(order);
    }

    static Order* getOrder(unsigned long int order_id) {
        return Model::db->getOrder(order_id);
    }

    /////////////   ADMINS   /////////////

    static Admin* getAdmin(Document& json) {
        Admin admin(json);
        Admin* source = Model::db->getAdmin(admin.getEmail());
        if (source == nullptr) {
            string mes = "Admin: the admin " + admin.getEmail() + " does not exist!";
            throw NotFoundException(mes);
        }
        if (Admin::compare_password(admin.getPassword(), source->getPassword()))
            throw ForbiddenException("Admin: the admin " + admin.getEmail() + " entered an incorrect password!");
        return source;
    }

    static unsigned long int createAdmin(Document& json) {
        Admin* admin;
        try {
            admin = getAdmin(json);
            return admin->getId();
        } catch (NotFoundException e) {
            admin = new Admin(json);
            return Model::db->createAdmin(*admin);
        }
    }

    /**
     * Returns information for admin according to data in JSON-file.
     * @param json - JSON-data with information about admin (email and password),
     * and special flag, according to which the information will be send.
     * @return complete JSON-string with information for admin.
     */
    static string getInfoAdmin(Document& json) {
        if (!json.HasMember("admin"))
            throw ForbiddenException("Input: input json file does not have admin data!");
        Document data;
        data.CopyFrom(json["admin"], json.GetAllocator());
        getAdmin(data);

        string res = "{\n";
        bool flag = false;
        IncorrectDataException exc;
        if (json.HasMember("passenger_id")) {
            if (!json["passenger_id"].IsInt64()) {
                exc.addEntry("passenger_id", "Passenger: Parameter 'passenger_id' has incorrect data type, expected: 'positive integer'");
                throw IncorrectDataException(exc.getErrors());
            }
            unsigned long int id = json["passenger_id"].GetInt64();
            Passenger* passenger = getPassenger(id);
            res += "passengers: [" + passenger->to_json_string() + "]";
            flag = true;
        }
        else if (json.HasMember("all_passengers")) {
            res += "passengers: [\n";
            vector<Passenger> passengers = Model::db->getAllPassengers();
            for (int i = 0; i < passengers.size(); i++) {
                res += passengers[i].to_json_string();
                res += ((i != passengers.size() - 1) ? ",\n" : "\n]");
            }
            flag = true;
        }

        if (json.HasMember("driver_id")) {
            if (!json["driver_id"].IsInt64()) {
                exc.addEntry("driver_id", "Driver: Parameter 'driver_id' has incorrect data type, expected: 'positive integer'");
                throw IncorrectDataException(exc.getErrors());
            }
            unsigned long int id = json["driver_id"].GetInt64();
            Driver* driver = getDriver(id);
            if (flag) res += ",\n";
            res += "drivers: [" + driver->to_json_string() + "]";
            flag = true;
        } else if (json.HasMember("all_drivers")) {
            if (flag) res += ",\n";
            res += "drivers: [\n";
            vector<Driver> drivers = Model::db->getAllDrivers();
            for (int i = 0; i < drivers.size(); i++) {
                res += drivers[i].to_json_string();
                res += ((i != drivers.size() - 1) ? ",\n" : "\n]");
            }
            flag = true;
        }

        if (json.HasMember("order_id")) {
            if (!json["order_id"].IsInt64()) {
                exc.addEntry("order_id", "Order: Parameter 'order_id' has incorrect data type, expected: 'positive integer'");
                throw IncorrectDataException(exc.getErrors());
            }
            unsigned long int id = json["order_id"].GetInt64();
            Order* order = getOrder(id);
            if (flag) res += ",\n";
            res += "orders: [" + order->to_json_string() + "]";
            flag = true;
        } else if (json.HasMember("all_orders")) {
            if (flag) res += ",\n";
            res += "orders: [\n";
            vector<Order> orders = Model::db->getAllOrders();
            for (int i = 0; i < orders.size(); i++) {
                res += orders[i].to_json_string();
                res += ((i != orders.size() - 1) ? ",\n" : "\n]");
            }
            flag = true;
        }


        if (json.HasMember("all_cars")) {
            if (flag) res += ",\n";
            res += "cars: [\n";
            vector<Car> cars = Model::db->getAllCars();
            for (int i = 0; i < cars.size(); i++) {
                res += cars[i].to_json_string();
                res += ((i != cars.size() - 1) ? ",\n" : "\n]");
            }
            flag = true;
        }
        if (json.HasMember("all_admins")) {
            if (flag) res += ",\n";
            res += "admins: [\n";
            vector<Admin> admins = Model::db->getAllAdmins();
            for (int i = 0; i < admins.size(); i++) {
                res += admins[i].to_json_string();
                res += ((i != admins.size() - 1) ? ",\n" : "\n]");
            }
        }
        res += "\n}";
        return res;
    }
};


#endif //PSS_MODEL_H
