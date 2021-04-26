//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_CAR_H
#define PSS_CAR_H

#include <utility>

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
    GEOAddress currentAddress{0, 0};    // forbidden
    string color;
    string number;  // identifier
    unsigned long int driver_id;
    unsigned int freeBottleOfWater;

public:
    Car(string number, string model, string color, CarType carType,
        unsigned int freeBottleOfWater, unsigned long int driver_id)
            : number(std::move(number)), model(std::move(model)), color(std::move(color)), carType(carType),
              freeBottleOfWater(freeBottleOfWater), driver_id(driver_id) {}

    Car(unsigned long int driver_id, rapidjson::Document& json) {
        validate_json(json);
        model = json["model"].GetString();
        string address = json["current_address"].GetString();
        currentAddress = GEOAddress(address);
        color = json["color"].GetString();
        number = json["number"].GetString();
        Car::driver_id = driver_id;

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

        if (json.HasMember("freeBottleOfWater") && json["freeBottleOfWater"].IsInt())
            freeBottleOfWater = json["number"].GetInt();
        else if (carType == CarType::Comfort) {
            srand(time(0));
            freeBottleOfWater = rand() % 10;
        }
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
            try {
                is_correct_type(check);
            } catch (IncorrectDataException) {
                exc.addEntry("car_type",
                             "Car: Parameter 'car_type' is incorrect, "
                             "expected: 'Economy', 'Comfort', 'ComfortPlus', 'Business', but given: " + check);
            }
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
     *  If the type is incorrect => throw an exception.
     */
    string is_correct_type(string& type) {
        string str = type;
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ')
                throw IncorrectDataException();
        }
        if (str == "economy" || str == "comfort" || str == "business" ||
                str == "comfortplus" || str == "comfort plus" || str == "comfort_plus")
            return str.c_str();
        throw IncorrectDataException();
    }

    string to_json_string() {
        string res = "{\ndriver_id: " + to_string(driver_id) + ",\n";
        res += "model: " + model + ",\n";
        res += "color: " + color + ",\n";
        res += "number: " + number + ",\n";
        if (carType == CarType::Economy)
            res += "car_type: economy\n}";
        else if (carType == CarType::Comfort)
            res += "car_type: comfort\n}";
        else if (carType == CarType::ComfortPlus)
            res += "car_type: comfort_plus\n}";
        else if (carType == CarType::Business)
            res += "car_type: business\n}";
        return res;
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

    const string &getModel() const {
        return model;
    }

    CarType getCarType() const {
        return carType;
    }

    const string &getColor() const {
        return color;
    }

    unsigned long getDriverId() const {
        return driver_id;
    }

    unsigned int getFreeBottleOfWater() const {
        return freeBottleOfWater;
    }

    void setDriverId(unsigned long driverId) {
        driver_id = driverId;
    }
};


#endif //PSS_CAR_H
