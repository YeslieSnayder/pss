//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_DRIVER_VIEW_H
#define PSS_DRIVER_VIEW_H

#include <vector>

using namespace std;
using namespace Pistache;

class DriverView {
public:
    void sendBadRequest(vector<IncorrectDataException::Entry> errors, Http::ResponseWriter& response) {
        string res = "{\n";
        for (int i = 0; i < errors.size() - 1; i++) {
            res += errors[i].key + ": " + errors[i].value + ",\n";
        }
        res += errors[errors.size()-1].key + ": " + errors[errors.size()-1].value + "\n}";
        response.send(Pistache::Http::Code::Bad_Request, res);
    }

    void sendNotFound(string message, Http::ResponseWriter& response) {
        string res = "{\nvalidation_error: {\nid: " + message + "\n}\n}";
        response.send(Pistache::Http::Code::Not_Found, res);
    }

    void sendForbidden(string message, Http::ResponseWriter& response) {
        string res = "{\npermission_denied: " + message + "\n}";
        response.send(Pistache::Http::Code::Forbidden, res);
    }

    void sendDriverCreated(unsigned long driver_id, Http::ResponseWriter& response) {
        string res = "{\nid: " + to_string(driver_id) + "\n}";
        response.send(Pistache::Http::Code::Created, res);
    }

    void sendDriverData(Driver& driver, Http::ResponseWriter& response) {
        string res = "{\n";
        res += "driver_id: " + to_string(driver.getId()) + ",\n";
        res += "name: " + driver.getName() + ",\n";
        res += "rating: " + to_string(driver.getRating()) + ",\n";
        res += "driver_status: ";

        if (driver.getStatus() == DriverStatus::NOT_WORKING)
            res += "not_working,\n";
        else if (driver.getStatus() == DriverStatus::WORKING)
            res += "working,\n";
        else if (driver.getStatus() == DriverStatus::IN_RIDE)
            res += "in_ride,\n";

        res += "personal_cars: " + getCarInfo(driver.getPersonalCars()) + "\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendListOrders(vector<Order>& orders, Http::ResponseWriter& response) {
        string res = "{\norders: [\n";
        for (int i = 0; i < orders.size() - 1; i++) {
            res += getOrderInfo(orders[i]) + ",\n";
        }
        if (!orders.empty())
            res += getOrderInfo(orders[orders.size()-1]);
        res += "]\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendCarInfo(vector<Car> cars, Http::ResponseWriter& response) {
        response.send(Pistache::Http::Code::Ok, getCarInfo(cars));
    }

    void sendOrderData(Order& order, Http::ResponseWriter& response) {
        response.send(Pistache::Http::Code::Ok, getOrderInfo(order));
    }

    void sendOrderId(unsigned long int order_id, Http::ResponseWriter& response) {
        string res = "{\norder_id: " + to_string(order_id) + "\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    string getCarInfo(vector<Car> cars) {
        string res;
        res = "{\ncars: [";
        for (int i = 0; i < cars.size(); i++) {
            Car car = cars[i];
            res = "{\n"
                  "driver_id: " + to_string(car.getDriverId()) + ",\n"
                  "model: " + car.getModel() + ",\n"
                  "color: " + car.getColor() + ",\n"
                  "number: " + car.getNumber() + ",\n";
            if (car.getCarType() == CarType::Economy)
                res += "car_type: economy\n";
            else if (car.getCarType() == CarType::Comfort)
                res += "car_type: comfort\n";
            else if (car.getCarType() == CarType::ComfortPlus)
                res += "car_type: comfort_plus\n";
            else if (car.getCarType() == CarType::Business)
                res += "car_type: business\n";
            res += ((i != cars.size() - 1) ? "}," : "}");
        }
        res += "]\n}";
        return res;
    }

    string getOrderInfo(Order& order) {
        string res = "{\norder_id: " + to_string(order.getId()) + ",\n"
            + "start_point: " + order.getStartPoint().geoString() + ",\n"
            + "destination: " + order.getDestination().geoString() + ",\n"
            + "start_time: " + order.getStartTime() + ",\n"
            + "passenger_id: " + to_string(order.getPassengerId()) + "\n}";
        return res;
    }
};


#endif //PSS_DRIVER_VIEW_H
