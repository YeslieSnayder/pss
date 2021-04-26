//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_DRIVER_VIEW_H
#define PSS_DRIVER_VIEW_H

#include <vector>
#include "../api/gateways/BaseGateway.h"

using namespace std;
using namespace Pistache;

class DriverView {
public:
    void sendBadRequest(vector<IncorrectDataException::Entry> errors, Http::ResponseWriter& response) {
        string res = "{";
        for (int i = 0; i < errors.size() - 1; i++) {
            res += errors[i].key + ": " + errors[i].value + ",";
        }
        if (!errors.empty())
            res += errors[errors.size()-1].key + ": " + errors[errors.size()-1].value;
        res += "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Bad_Request, res);
    }

    void sendNotFound(string message, Http::ResponseWriter& response) {
        string res = "{validation_error: {id: " + message + "}}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Not_Found, res);
    }

    void sendForbidden(string message, Http::ResponseWriter& response) {
        string res = "{permission_denied: " + message + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Forbidden, res);
    }

    void sendDriverCreated(unsigned long driver_id, Http::ResponseWriter& response) {
        string res = "{id: " + to_string(driver_id) + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Created, res);
    }

    void sendDriverData(Driver& driver, Http::ResponseWriter& response, Pistache::Http::Code code=Pistache::Http::Code::Ok) {
        string res = "{";
        res += "driver_id: " + to_string(driver.getId()) + ",";
        res += "name: " + driver.getName() + ",";
        res += "rating: " + to_string(driver.getRating()) + ",";
        res += "driver_status: ";

        if (driver.getStatus() == DriverStatus::NOT_WORKING)
            res += "not_working,";
        else if (driver.getStatus() == DriverStatus::WORKING)
            res += "working,";
        else if (driver.getStatus() == DriverStatus::IN_RIDE)
            res += "in_ride,";

        res += "personal_cars: [";
        int i = 0;
        for (; i < driver.getPersonalCars().size() - 1; i++) {
            Car car = driver.getPersonalCars()[i];
            res += getCarInfo(car) + ",";
        }
        if (!driver.getPersonalCars().empty()) {
            Car car = driver.getPersonalCars()[i];
            res += getCarInfo(car);
        }
        res += "]}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(code, res);
    }

    void sendListOrders(vector<Order>& orders, Http::ResponseWriter& response) {
        string res = "{orders: [";
        for (int i = 0; i < orders.size() - 1; i++) {
            res += getOrderInfo(orders[i]) + ",";
        }
        if (!orders.empty())
            res += getOrderInfo(orders[orders.size()-1]);
        res += "]}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendCarInfo(vector<Car> cars, Http::ResponseWriter& response) {
        string res = "{cars: [";
        for (int i = 0; i < cars.size()-1; i++) {
            res += getCarInfo(cars[i]) + ",";
        }
        if (!cars.empty())
            res += getCarInfo(cars[cars.size()-1]);
        res += "]}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendOrderData(Order& order, Http::ResponseWriter& response) {
        string res = getOrderInfo(order);
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendOrderId(unsigned long int order_id, Http::ResponseWriter& response) {
        string res = "{order_id: " + to_string(order_id) + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    string getCarInfo(Car &car) {
        string res;
        res = "{"
              "driver_id: " + to_string(car.getDriverId()) + ","
              "model: " + car.getModel() + ","
              "color: " + car.getColor() + ","
              "number: " + car.getNumber() + ",";
        if (car.getCarType() == CarType::Economy)
            res += "car_type: economy";
        else if (car.getCarType() == CarType::Comfort)
            res += "car_type: comfort";
        else if (car.getCarType() == CarType::ComfortPlus)
            res += "car_type: comfort_plus";
        else if (car.getCarType() == CarType::Business)
            res += "car_type: business";
        res += "}";
        return res;
    }

    string getOrderInfo(Order& order) {
        string res = "{order_id: " + to_string(order.getId()) + ","
            + "start_point: " + order.getStartPoint().geoString() + ","
            + "destination: " + order.getDestination().geoString() + ","
            + "start_time: " + order.getStartTime() + ","
            + "passenger_id: " + to_string(order.getPassengerId()) + "}";
        return res;
    }
};


#endif //PSS_DRIVER_VIEW_H
