//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_PASSENGER_VIEW_H
#define PSS_PASSENGER_VIEW_H

#include <vector>

using namespace std;

class PassengerView {
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
        string res = "{\nvalidation error: {\nid: " + message + "\n}\n}";
        response.send(Pistache::Http::Code::Not_Found, res);
    }

    void sendPassengerCreated(unsigned long int id, Http::ResponseWriter& response) {
        string res = "{\nid: " + to_string(id) + "\n}";
        response.send(Pistache::Http::Code::Created, res);
    }

    void sendPassengerData(Passenger& passenger, Http::ResponseWriter& response) {
        string res = "{\n";
        res += "passenger_id: " + to_string(passenger.getId()) + ",\n";
        res += "name: " + passenger.getName() + ",\n";
        res += "rating: " + to_string(passenger.getRating()) + ",\n";
        res += "payment_method: ";
        if (passenger.getPaymentMethod() == PaymentMethod::CASH)
            res += "cash,\n";
        else if (passenger.getPaymentMethod() == PaymentMethod::ONLINE)
            res += "online,\n";
        else if (passenger.getPaymentMethod() == PaymentMethod::BANK_BILL)
            res += "bank_bill,\n";
        res += "pinned_addresses: [\n";
        for (int i = 0; i < passenger.getPinnedAddresses().size() - 1; i++) {
            res += passenger.getPinnedAddresses()[i].geoString() + ",\n";
        }
        if (!passenger.getPinnedAddresses().empty())
            res += passenger.getPinnedAddresses()[passenger.getPinnedAddresses().size() - 1].geoString() + "\n";
        res += "]\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendPreOrderData(PreOrder order, Http::ResponseWriter& response) {
        string res = "{\norder: {\n";
        res += "time: " + to_string(order.time) + ",\n";
        res += "distance: " + to_string(order.distance) + ",\n";
        res += "price: " + to_string(order.price) + ",\n}\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendOrderData(Order order, Http::ResponseWriter& response) {
        response.send(Pistache::Http::Code::Ok, getOrderInfo(order));
    }

    void sendCarInfo(Car car, Http::ResponseWriter& response) {
        string res;
        res = "{\ncar: {\n"
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
        res += "}\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendOrderHistory(vector<Order>& orders, Http::ResponseWriter& response) {
        string res = "{\norders: [\n";
        for (int i = 0; i < orders.size() - 1; i++) {
            res += getOrderInfo(orders[i]) + ",\n";
        }
        if (!orders.empty())
            res += getOrderInfo(orders[orders.size()-1]);
        res += "]\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    string getOrderInfo(Order& order) {
        return "{\norder_id: " + to_string(order.getId()) + ",\n"
               "start_point: " + order.getStartPoint().geoString() + ",\n"
               "destination: " + order.getDestination().geoString() + ",\n"
               "start_time: " + order.getStartTime() + ",\n"
               "passenger_id: " + to_string(order.getPassengerId()) + "\n}";
    }
};

#endif //PSS_PASSENGER_VIEW_H
