//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVER_H
#define PSS_DRIVER_H

#include <utility>
#include <vector>
#include "rapidjson/document.h"

#include "../exceptions/IncorrectDataException.h"
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
        validate_json(json);
        name = json["passenger"]["name"].Get<string>();
        rating = json["passenger"]["rating"].Get<float>();

        string status_str = json["passenger"]["driver_status"].Get<string>();
        status_str = is_correct_status(status_str);
        if (status_str == "not_working" || status_str == "not working")
            status = DriverStatus::NOT_WORKING;
        else if (status_str == "in_ride" || status_str == "in ride")
            status = DriverStatus::IN_RIDE;
        else if (status_str == "working")
            status = DriverStatus::WORKING;

        rapidjson::Document carDoc;
        carDoc.Accept(json["passenger"]["personal_car"]);
        personalCar = new Car(carDoc);
    }

    /**
     * Validates the data from json file.
     * @param document - json file with passenger data.
     */
    void validate_json(const rapidjson::Document& json) {
        if (!json.HasMember("passenger"))
            throw IncorrectDataException("passenger", "Body does not have required key: passenger");
        IncorrectDataException exc;
        if (!json["passenger"].HasMember("name"))
            exc.addEntry("name", "Body does not have parameter 'name'");
        if (!json["passenger"].HasMember("rating"))
            exc.addEntry("rating", "Body does not have parameter 'rating'");
        if (!json["passenger"].HasMember("personal_car"))
            exc.addEntry("personal_car", "Body does not have parameter 'personal_car'");
        if (!json["passenger"].HasMember("driver_status"))
            exc.addEntry("driver_status", "Body does not have parameter 'driver_status'");

        if (json["passenger"].HasMember("name") && !json["passenger"]["name"].IsString())
            exc.addEntry("name", "Parameter 'name' is incorrect, expected type: 'string'");
        if (json["passenger"].HasMember("rating") && !json["passenger"]["rating"].IsNumber())
            exc.addEntry("rating", "Parameter 'rating' is incorrect, expected type: 'number'");
        if (json["passenger"].HasMember("personal_car") && !json["passenger"]["personal_car"].IsObject())
            exc.addEntry("personal_car", "Parameter 'personal_car' is incorrect, expected type: 'object'");
        if (json["passenger"].HasMember("driver_status") && !json["passenger"]["driver_status"].IsString())
            exc.addEntry("driver_status", "Parameter 'driver_status' is incorrect, expected type: 'string'");

        if (json["passenger"].HasMember("rating") && json["passenger"]["rating"].IsNumber()) {
            auto check = json["passenger"]["rating"].Get<float>();
            if (check < 0.0 || check > 5.0)
                exc.addEntry("rating",
                             "Parameter 'rating' is out of range, expected: 0 <= value <= 5.0, but given: " +
                             to_string(check));
        }
        if (json["passenger"].HasMember("driver_status") && json["passenger"]["driver_status"].IsString()) {
            auto check = json["passenger"]["driver_status"].Get<string>();
            if (!is_correct_status(check))
                exc.addEntry("driver_status",
                             "Parameter 'driver_status' is incorrect, "
                             "expected: 'not_working', 'working', 'in_ride', but given: " + check);
        }

        if (exc.hasErrors())
            throw exc;
    }

    /**
     * Checks the validity of status and return the string in the lowercase if the status is correct,
     *  otherwise - null pointer.
     * @param status - string represented status of the driver.
     * @return If the status is correct => pointer to first element of the status string (in lowercase),
     *  otherwise => null pointer (nullptr).
     */
    const char* is_correct_status(string &status) {
        string str = move(status);
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && (c != '_' || c != ' '))
                return nullptr;
        }
        if (str == "not_working" || str == "not working" || str == "in_ride" || str == "in ride" || str == "working")
            return str.c_str();
        return nullptr;
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

    void setId(unsigned long id) {
        Driver::id = id;
    }

    unsigned long getId() const {
        return id;
    }
};


#endif //PSS_DRIVER_H
