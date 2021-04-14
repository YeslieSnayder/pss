//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_CAR_H
#define PSS_CAR_H

#include "Address.h"
#include "rapidjson/document.h"
#include "../exceptions/IncorrectDataException.h"

using namespace std;

enum class CarType {
    Economy,
    Comfort,
    ComfortPlus,
    Business
};

class Car {
    string model;
    CarType carType;
    GEOAddress currentAddress{0, 0};
    string color;
    string number;
    unsigned long int driver_id;
    unsigned int freeBottleOfWater;

public:
    Car(const string &model, CarType carType, const GEOAddress &currentAddress, const string &color,
        const string &number, unsigned long driverId, unsigned int freeBottleOfWater) : model(model), carType(carType),
                                currentAddress(currentAddress), color(color), number(number), driver_id(driverId) {}

    Car(unsigned long int driver_id, rapidjson::Document& json) {
        validate_json(json);
        model = json["model"].GetString();
        string address = json["current_address"].GetString();
        currentAddress = GEOAddress(address);
        color = json["color"].GetString();
        number = json["number"].GetString();
        Car::driver_id = driver_id;
        if (json.HasMember("freeBottleOfWater") && json["freeBottleOfWater"].IsInt())
            freeBottleOfWater = json["number"].GetInt();

        string type = json["car_type"].GetString();
        type = is_correct_type(type);
        if (type == "economy")
            carType = CarType::Economy;
        else if (type == "comfort")
            carType = CarType::Comfort;
        else if (type == "business")
            carType = CarType::Business;
        else if (type == "comfortplus" || type == "comfort_plus" || type == "comfort plus")
            carType = CarType::ComfortPlus;
    }

    /**
     * Validates the data from json file.
     * @param json - json file with passenger data.
     */
    void validate_json(const rapidjson::Document& json) {
        IncorrectDataException exc;
        if (!json.HasMember("model"))
            exc.addEntry("model", "Car: Body does not have parameter 'model'");
        if (!json.HasMember("car_type"))
            exc.addEntry("car_type", "Car: Body does not have parameter 'car_type'");
        if (!json.HasMember("current_address"))
            exc.addEntry("current_address", "Car: Body does not have parameter 'current_address'");
        if (!json.HasMember("color"))
            exc.addEntry("color", "Car: Body does not have parameter 'color'");
        if (!json.HasMember("number"))
            exc.addEntry("number", "Car: Body does not have parameter 'number'");

        if (json.HasMember("model") && !json["model"].IsString())
            exc.addEntry("model", "Car: Parameter 'model' is incorrect, expected type: 'string'");
        if (json.HasMember("car_type") && !json["car_type"].IsString())
            exc.addEntry("car_type", "Car: Parameter 'car_type' is incorrect, expected type: 'string'");
        if (json.HasMember("current_address") && !json["current_address"].IsString())
            exc.addEntry("current_address", "Car: Parameter 'current_address' is incorrect, expected type: 'string'");
        if (json.HasMember("color") && !json["color"].IsString())
            exc.addEntry("color", "Car: Parameter 'color' is incorrect, expected type: 'string'");
        if (json.HasMember("number") && !json["number"].IsString())
            exc.addEntry("number", "Car: Parameter 'number' is incorrect, expected type: 'string'");
        if (json.HasMember("freeBottleOfWater") && !json["freeBottleOfWater"].IsInt())
            exc.addEntry("freeBottleOfWater", "Car: Parameter 'freeBottleOfWater' is incorrect, expected type: 'integer'");

        if (json.HasMember("car_type") && json["car_type"].IsString()) {
            string check = json["car_type"].GetString();
            if (is_correct_type(check) == nullptr)
                exc.addEntry("car_type",
                             "Car: Parameter 'car_type' is incorrect, "
                             "expected: 'Economy', 'Comfort', 'ComfortPlus', 'Business', but given: " + check);
        }
        if (json.HasMember("number") && json["number"].IsString()) {
            string check = json["number"].GetString();
            if (!(check.size() == 6 && (check[0] >= 'A' && check[0] <= 'Z' || check[0] >= 'a' && check[0] <= 'z')))
                exc.addEntry("number",
                             "Car: Parameter 'number' is incorrect, expected: 6 signs, first has to be letter"
                             ", but given: " + check);
        }
        if (json.HasMember("freeBottleOfWater") && json["freeBottleOfWater"].IsInt()) {
            int check = json["freeBottleOfWater"].GetInt();
            if (check < 0)
                exc.addEntry("freeBottleOfWater",
                             "Car: Parameter 'freeBottleOfWater' is incorrect, expected: positive integer"
                             ", but given: " + to_string(check));
        }

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());
    }

    /**
     * Checks the validity of a car type. Returns car type in lowercase, if the type is correct,
     *  otherwise null pointer.
     * @param type - string represented the type of the car.
     * @return If the type is correct => string that represented a type in lowercase,
     *  If the type is incorrect => null pointer (nullptr).
     */
    const char* is_correct_type(string& type) {
        string str = type;
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ')
                return nullptr;
        }
        if (str == "economy" || str == "comfort" || str == "business" ||
                str == "comfortplus" || str == "comfort plus" || str == "comfort_plus")
            return str.c_str();
        return nullptr;
    }

    bool operator==(const Car& obj) const {
        return model == obj.model && carType == obj.carType && currentAddress == obj.currentAddress
                && color == obj.color && number == obj.number;
    }

    bool operator!=(const Car& obj) const {
        return !(operator==(obj));
    }

    const string &getNumber() const {
        return number;
    }
};


#endif //PSS_CAR_H
