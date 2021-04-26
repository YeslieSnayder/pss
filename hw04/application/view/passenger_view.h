//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_PASSENGER_VIEW_H
#define PSS_PASSENGER_VIEW_H

#include <vector>

#include "../api/gateways/BaseGateway.h"

using namespace std;

class PassengerView {
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

    void sendPassengerCreated(unsigned long int id, Http::ResponseWriter& response) {
        string res = "{id: " + to_string(id) + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Created, res);
    }

    void sendPassengerData(Passenger& passenger, Http::ResponseWriter& response, Pistache::Http::Code code=Pistache::Http::Code::Ok) {
        string res = "{";
        res += "passenger_id: " + to_string(passenger.getId()) + ",";
        res += "name: " + passenger.getName() + ",";
        res += "rating: " + to_string(passenger.getRating()) + ",";
        res += "payment_method: ";
        if (passenger.getPaymentMethod() == PaymentMethod::CASH)
            res += "cash,";
        else if (passenger.getPaymentMethod() == PaymentMethod::ONLINE)
            res += "online,";
        else if (passenger.getPaymentMethod() == PaymentMethod::BANK_BILL)
            res += "bank_bill,";
        res += "pinned_addresses: [";
        for (int i = 0; i < passenger.getPinnedAddresses().size() - 1; i++) {
            string address = passenger.getPinnedAddresses()[i].geoString();
            if (address.empty())
                break;
            res += address + ",";
        }
        if (!passenger.getPinnedAddresses().empty()) {
            string address = passenger.getPinnedAddresses()[passenger.getPinnedAddresses().size() - 1].geoString();
            if (!address.empty())
                res += address;
        }
        res += "]}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(code, res);
    }

    void sendPreOrderData(PreOrder order, Http::ResponseWriter& response) {
        string res = "{order: {";
        res += "time: " + to_string(order.time) + ",";
        res += "distance: " + to_string(order.distance) + ",";
        res += "price: " + to_string(order.price) + ",}}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendOrderData(Order order, Http::ResponseWriter& response) {
        string res = getOrderInfo(order);
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendCarInfo(Car car, Http::ResponseWriter& response) {
        string res;
        res = "{car: {"
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
        res += "}}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendOrderHistory(vector<Order>& orders, Http::ResponseWriter& response) {
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

    string getOrderInfo(Order& order) {
        return "{order_id: " + to_string(order.getId()) + ","
               "start_point: " + order.getStartPoint().geoString() + ","
               "destination: " + order.getDestination().geoString() + ","
               "start_time: " + order.getStartTime() + ","
               "passenger_id: " + to_string(order.getPassengerId()) + "}";
    }
};

#endif //PSS_PASSENGER_VIEW_H
