//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVER_H
#define PSS_DRIVER_H

#include <utility>
#include <vector>
#include "rapidjson/document.h"

#include "User.h"
#include "Car.h"
#include "Order.h"
#include "../exceptions/IncorrectDataException.h"

using namespace std;

enum class DriverStatus : int {
    NOT_WORKING,
    WORKING,
    IN_RIDE
};

class Driver : public User {
    double rating;   // 0.0 <= value <= 5.0
    vector<Order> orderHistory;
    vector<Car> personalCars;
    DriverStatus status;

public:
    Driver(unsigned long int id, string& name, double rating,
           vector<Car> personalCars, DriverStatus status) : rating(rating), personalCars(personalCars), status(status) {
        Driver::id = id;
        Driver::name = std::move(name);
    }

    Driver(rapidjson::Document& json) {
        validate_json(json);
        name = json["name"].GetString();
        rating = json["rating"].GetDouble();

        string status_str = json["driver_status"].GetString();
        status_str = is_correct_status(status_str);
        if (status_str == "not_working" || status_str == "not working")
            status = DriverStatus::NOT_WORKING;
        else if (status_str == "in_ride" || status_str == "in ride")
            status = DriverStatus::IN_RIDE;
        else if (status_str == "working")
            status = DriverStatus::WORKING;

        rapidjson::Document doc;
        for (int i = 0; i < json["personal_cars"].Size(); ++i) {
            doc.CopyFrom(json["personal_cars"][i], json.GetAllocator());
            Car car = *(new Car(id, doc));
            personalCars.push_back(car);
        }

        if (json.HasMember("driver_id") && json["driver_id"].IsInt())
            id = json["driver_id"].GetInt();

        if (json.HasMember("order_history")) {
            orderHistory.clear();
            for (int i = 0; i < json["order_history"].GetArray().Size(); i++) {
                rapidjson::Document doc;
                doc.CopyFrom(json["order_history"][i], json.GetAllocator());
                Order order(doc);
                orderHistory.push_back(order);
            }
        }
    }

    void patch(rapidjson::Document& json) {
        validate_json(json, false);
        if (json.HasMember("name"))
            name = json["name"].GetString();
        if (json.HasMember("rating"))
            rating = json["rating"].GetDouble();

        if (json.HasMember("driver_status")) {
            string status_str = json["driver_status"].GetString();
            status_str = is_correct_status(status_str);
            if (status_str == "not_working" || status_str == "not working")
                status = DriverStatus::NOT_WORKING;
            else if (status_str == "in_ride" || status_str == "in ride")
                status = DriverStatus::IN_RIDE;
            else if (status_str == "working")
                status = DriverStatus::WORKING;
        }

        if (json.HasMember("personal_car")) {
            rapidjson::Document doc;
            for (int i = 0; i < json["personal_cars"].Size(); ++i) {
                doc.CopyFrom(json["personal_cars"][i], json.GetAllocator());
                Car car = *(new Car(id, doc));
                personalCars.push_back(car);
            }
        }

        if (json.HasMember("order_history")) {
            orderHistory.clear();
            for (int i = 0; i < json["order_history"].GetArray().Size(); i++) {
                rapidjson::Document doc;
                doc.CopyFrom(json["order_history"][i], json.GetAllocator());
                Order order(doc);
                orderHistory.push_back(order);
            }
        }
    }

    /**
     * Validates the data from json file.
     * @param json - json file with driver's data.
     * @param is_creation - flag for checking JSON-file while creating of driver.
     */
    void validate_json(const rapidjson::Document& json, bool is_creation=true) {
        IncorrectDataException exc;

        if (is_creation && !json.HasMember("name"))
            exc.addEntry("name", "Driver: Body does not have parameter 'name'");
        else if (json.HasMember("name")) {
            if (!json["name"].IsString())
                exc.addEntry("name", "Driver: Parameter 'name' is incorrect, expected type: 'string'");
            else {
                string check = json["name"].GetString();
                if (check.empty())
                    exc.addEntry("name", "Driver: Parameter 'name' is incorrect, name should contain minimum 1 letter");
                for (char &c : check) {
                    if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ' && c != '-') {
                        exc.addEntry("name", "Driver: Parameter 'name' is incorrect,"
                                             " name should not contain any characters except letters");
                        break;
                    }
                }
            }
        }

        if (is_creation && !json.HasMember("rating"))
            exc.addEntry("rating", "Driver: Body does not have parameter 'rating'");
        else if (json.HasMember("rating")) {
            if (!json["rating"].IsNumber())
                exc.addEntry("rating", "Driver: Parameter 'rating' is incorrect, expected type: 'number'");
            else {
                float check = json["rating"].GetFloat();
                if (check < 0.0 || check > 5.0)
                    exc.addEntry("rating",
                                 "Driver: Parameter 'rating' is out of range, expected: 0 <= value <= 5.0, but given: " +
                                 to_string(check));
            }
        }

        if (is_creation && !json.HasMember("personal_cars"))
            exc.addEntry("personal_cars", "Driver: Body does not have parameter 'personal_cars'");
        else if (json.HasMember("personal_cars")) {
            if (!json["personal_cars"].IsArray())
                exc.addEntry("personal_cars", "Driver: Parameter 'personal_cars' is incorrect, expected type: 'array'");
        }

        if (is_creation && !json.HasMember("driver_status"))
            exc.addEntry("driver_status", "Driver: Body does not have parameter 'driver_status'");
        else if (json.HasMember("driver_status")) {
            if (!json["driver_status"].IsString())
                exc.addEntry("driver_status",
                             "Driver: Parameter 'driver_status' is incorrect, expected type: 'string'");
            else {
                string check = json["driver_status"].GetString();
                try {
                    is_correct_status(check);
                } catch (IncorrectDataException) {
                    exc.addEntry("driver_status",
                                 "Driver: Parameter 'driver_status' is incorrect, "
                                 "expected: 'not_working', 'working', 'in_ride', but given: " + check);
                }
            }
        }

        if (json.HasMember("driver_id") && !json["driver_id"].IsInt())
            exc.addEntry("driver_id", "Driver: Parameter 'driver_id' is incorrect, expected type: 'integer'");
        else if (json.HasMember("driver_id") && json["driver_id"].IsInt()) {
            int driver_id = json["driver_id"].GetInt();
            if (driver_id < 0)
                exc.addEntry("driver_id",
                             "Driver: Parameter 'driver_id' is incorrect, expected: positive integer"
                             ", but given: " + to_string(driver_id));
        }

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());
    }

    /**
     * Checks the validity of status and return the string in the lowercase if the status is correct,
     *  otherwise - null pointer.
     * @param status - string represented status of the driver.
     * @return If the status is correct => status string (in lowercase),
     *  otherwise => throw an exception.
     */
    string is_correct_status(string &status) {
        string str = status;
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ')
                throw IncorrectDataException();
        }
        if (str == "not_working" || str == "not working" || str == "in_ride" || str == "in ride" || str == "working")
            return str;
        throw IncorrectDataException();
    }

    bool operator==(const Driver& obj) const {
        if (name == obj.name && rating == obj.rating && status == obj.status
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

    void setId(unsigned long id) {
        Driver::id = id;
    }

    unsigned long getId() const {
        return id;
    }

    const string &getName() const {
        return name;
    }

    double getRating() const {
        return rating;
    }

    const vector<Order> &getOrderHistory() const {
        return orderHistory;
    }

    const vector<Car> &getPersonalCars() const {
        return personalCars;
    }

    DriverStatus getStatus() const {
        return status;
    }

    void setName(const string &name) {
        Driver::name = name;
    }

    void setRating(double rating) {
        Driver::rating = rating;
    }

    void setOrderHistory(const vector<Order> &orderHistory) {
        Driver::orderHistory = orderHistory;
    }

    void setStatus(DriverStatus status) {
        Driver::status = status;
    }
};


#endif //PSS_DRIVER_H
