//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_PASSENGER_VIEW_H
#define PSS_PASSENGER_VIEW_H

#include <vector>
#include <iostream>

using namespace std;

class PassengerView {
public:
    void sendIdOK(unsigned long int id, Http::ResponseWriter& response) {
        string res = "{\nid: " + to_string(id) + "\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendBadRequest(vector<IncorrectDataException::Entry> errors, Http::ResponseWriter& response) {
        string res = "{\n";
        for (int i = 0; i < errors.size() - 1; i++) {
            res += errors[i].key + ": " + errors[i].value + ",\n";
        }
        res += errors[errors.size()-1].key + ": " + errors[errors.size()-1].value + "\n}";
        response.send(Pistache::Http::Code::Bad_Request, res);
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
        if (passenger.getPinnedAddresses().size() != 0)
            res += passenger.getPinnedAddresses()[passenger.getPinnedAddresses().size() - 1].geoString() + "\n";
        res += "]\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendNotFound(const string& message, Http::ResponseWriter& response) {
        string res = "{\nvalidation error: {\nid: " + message + "\n}\n}";
        response.send(Pistache::Http::Code::Not_Found, res);
    }
};

#endif //PSS_PASSENGER_VIEW_H
