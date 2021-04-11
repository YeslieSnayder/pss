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

    Driver(rapidjson::Document& json) {
        validate_json(json);
        name = json["name"].GetString();
        rating = json["rating"].GetFloat();

        string status_str = json["driver_status"].GetString();
        status_str = is_correct_status(status_str);
        if (status_str == "not_working" || status_str == "not working")
            status = DriverStatus::NOT_WORKING;
        else if (status_str == "in_ride" || status_str == "in ride")
            status = DriverStatus::IN_RIDE;
        else if (status_str == "working")
            status = DriverStatus::WORKING;

        rapidjson::Document doc;
        doc.CopyFrom(json["personal_car"], json.GetAllocator());
        personalCar = new Car(doc);

        // TODO: Add method to add orderHistory
    }

    /**
     * Validates the data from json file.
     * @param json - json file with passenger data.
     */
    void validate_json(const rapidjson::Document& json) {
        IncorrectDataException exc;
        if (!json.HasMember("name"))
            exc.addEntry("name", "Driver: Body does not have parameter 'name'");
        if (!json.HasMember("rating"))
            exc.addEntry("rating", "Driver: Body does not have parameter 'rating'");
        if (!json.HasMember("personal_car"))
            exc.addEntry("personal_car", "Driver: Body does not have parameter 'personal_car'");
        if (!json.HasMember("driver_status"))
            exc.addEntry("driver_status", "Driver: Body does not have parameter 'driver_status'");

        if (json.HasMember("name") && !json["name"].IsString())
            exc.addEntry("name", "Driver: Parameter 'name' is incorrect, expected type: 'string'");
        if (json.HasMember("rating") && !json["rating"].IsNumber())
            exc.addEntry("rating", "Driver: Parameter 'rating' is incorrect, expected type: 'number'");
        if (json.HasMember("personal_car") && !json["personal_car"].IsObject())
            exc.addEntry("personal_car", "Driver: Parameter 'personal_car' is incorrect, expected type: 'object'");
        if (json.HasMember("driver_status") && !json["driver_status"].IsString())
            exc.addEntry("driver_status", "Driver: Parameter 'driver_status' is incorrect, expected type: 'string'");

        if (json.HasMember("rating") && json["rating"].IsNumber()) {
            auto check = json["rating"].Get<float>();
            if (check < 0.0 || check > 5.0)
                exc.addEntry("rating",
                             "Driver: Parameter 'rating' is out of range, expected: 0 <= value <= 5.0, but given: " +
                             to_string(check));
        }
        if (json.HasMember("driver_status") && json["driver_status"].IsString()) {
            string check = json["driver_status"].GetString();
            if (is_correct_status(check) == nullptr)
                exc.addEntry("driver_status",
                             "Driver: Parameter 'driver_status' is incorrect, "
                             "expected: 'not_working', 'working', 'in_ride', but given: " + check);
        }

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());
    }

    /**
     * Checks the validity of status and return the string in the lowercase if the status is correct,
     *  otherwise - null pointer.
     * @param status - string represented status of the driver.
     * @return If the status is correct => pointer to first element of the status string (in lowercase),
     *  otherwise => null pointer (nullptr).
     */
    const char* is_correct_status(string &status) {
        string str = status;
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ')
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
