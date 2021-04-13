//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_ORDER_H
#define PSS_ORDER_H

#include <ctime>
#include "rapidjson/document.h"

#include "Address.h"
#include "Car.h"

enum class OrderStatus : int {
    READY,
    PROCESSING,
    COMPLETE
};

class PreOrder {
    unsigned long int time; // time for the ride (in minutes)
    unsigned long int distance; // distance from start point and destination
    unsigned long int price;    // price for the ride

public:
    PreOrder(rapidjson::Document& json) {
        validate_json(json);

        string s = json["start_point"].GetString();
        GEOAddress start(s);
        s = json["destination"].GetString();
        GEOAddress end(s);

        CarType carType;
        s = json["car_type"].GetString();
        if (s == "economy")
            carType = CarType::Economy;     // coefficient => 5
        else if (s == "comfort")
            carType = CarType::Comfort;     // coefficient => 10
        else if (s == "business")
            carType = CarType::Business;    // coefficient => 20
        else if (s == "comfortplus" && s == "comfort plus" && s == "comfort_plus")
            carType = CarType::ComfortPlus; // coefficient => 15

        const int for_time = 60;            // constant: minutes per unit of distance
        const double km_per_unit = 71.608;  // constant: kilometers per unit of distance
        const int price_per_km = 9;         // constant: rubles per kilometer

        double d = GEOAddress::getDistance(start, end);
        time = for_time * d;
        distance = km_per_unit * d;
        price = price_per_km * distance;
    }

    /**
     * Validates the data from json file.
     * @param json - json file with preorder's data.
     */
    void validate_json(rapidjson::Document& json) {
        IncorrectDataException exc;

        if (!json.HasMember("start_point"))
            exc.addEntry("start_point", "Preorder: Body does not have parameter 'start_point'");
        else if (!json["start_point"].IsString())
            exc.addEntry("start_point", "Preorder: Parameter 'start_point' is incorrect, expected type: 'string'");

        if (!json.HasMember("destination"))
            exc.addEntry("destination", "Preorder: Body does not have parameter 'destination'");
        else if (!json["destination"].IsString())
            exc.addEntry("destination", "Preorder: Parameter 'destination' is incorrect, expected type: 'string'");

        if (!json.HasMember("car_type"))
            exc.addEntry("car_type", "Preorder: Body does not have parameter 'car_type'");
        else if (!json["car_type"].IsString())
            exc.addEntry("car_type", "Preorder: Parameter 'car_type' is incorrect, expected type: 'string'");
        else {
            string str = json["car_type"].GetString();
            for (char &c : str) {
                if (c >= 'A' && c <= 'Z')
                    c = c + ('a' - 'A');
                if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ') {
                    exc.addEntry("car_type", "Preorder: Parameter 'car_type' is incorrect, "
                                             "expected: 'economy', 'comfort', 'business', 'comfort_plus', but given: " + str);
                    break;
                }
            }
            if (str != "economy" && str != "comfort" && str != "business" &&
                    str != "comfortplus" && str != "comfort plus" && str != "comfort_plus") {
                exc.addEntry("car_type", "Preorder: Parameter 'car_type' is incorrect, "
                                         "expected: 'economy', 'comfort', 'business', 'comfort_plus', but given: " + str);
            }
        }

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());
    }
};

class Order {
    static const unsigned long int NULL_ID = 0;

    unsigned long int id = NULL_ID;
    GEOAddress startPoint{0,0};
    GEOAddress destination{0,0};
    std::time_t startTime;
    Car* car;
    float price;
    unsigned long int passenger_id;
    unsigned long int driver_id;

    OrderStatus status;

public:
    Order(rapidjson::Document& json) {
        validate_json(json);

        driver_id = json["driver_id"].GetInt();

        string s = json["start_point"].GetString();
        GEOAddress start(s);
        startPoint = start;

        s = json["destination"].GetString();
        GEOAddress end(s);
        destination = end;

        s = json["start_time"].GetString();
        // TODO: Assign start time
    }
    Order(rapidjson::Document& json, unsigned long int passenger_id) : Order(json) {
        Order::passenger_id = passenger_id;
    }

    /**
     * Validates the data from json file.
     * @param json - json file with order's data.
     */
    void validate_json(rapidjson::Document& json) {
        IncorrectDataException exc;


    }

    bool operator==(const Order& obj) const {
        return startPoint == obj.startPoint && destination == obj.destination && startTime == obj.startTime
            && passenger_id == obj.passenger_id && driver_id == obj.driver_id;
    }

    bool operator!=(const Order& obj) const {
        return !(operator==(obj));
    }

    unsigned long getId() const {
        return id;
    }

    unsigned long getPassengerId() const {
        return passenger_id;
    }

    unsigned long getDriverId() const {
        return driver_id;
    }

    OrderStatus getStatus() const {
        return status;
    }

    void setCar(Car *car) {
        Order::car = car;
    }

    void setDriverId(unsigned long driverId) {
        driver_id = driverId;
    }

    void setStatus(OrderStatus status) {
        Order::status = status;
    }
};


#endif //PSS_ORDER_H
