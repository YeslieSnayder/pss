//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGER_H
#define PSS_PASSENGER_H

#include <utility>
#include <vector>
#include "rapidjson/document.h"

#include "User.h"
#include "Order.h"
#include "Address.h"

using namespace std;

enum class PaymentMethod {
    CASH,
    ONLINE,
    BANK_BILL
};

class Passenger : public User {
    double rating;
    vector<Order> orderHistory;
    vector<GEOAddress> pinnedAddresses;
    PaymentMethod paymentMethod;

public:

    Passenger(unsigned long id, string& name, double rating, PaymentMethod paymentMethod)
            : rating(rating), paymentMethod(paymentMethod) {
        Passenger::id = id;
        Passenger::name = std::move(name);
        pinnedAddresses = vector<GEOAddress>();
    }

    Passenger(rapidjson::Document& json) {
        validate_json(json);
        name = json["name"].GetString();
        rating = json["rating"].GetDouble();

        for (const auto& address : json["pinned_addresses"].GetArray()) {
            string address_str = address.GetString();
            GEOAddress geoAddress(address_str);
            pinnedAddresses.push_back(geoAddress);
        }

        string payment_str = json["payment_method"].GetString();
        string payment = is_correct_payment(payment_str);
        if (payment == "cash")
            paymentMethod = PaymentMethod::CASH;
        else if (payment == "online")
            paymentMethod = PaymentMethod::ONLINE;
        else if (payment == "bank_bill" || payment == "bank bill")
            paymentMethod = PaymentMethod::BANK_BILL;

        if (json.HasMember("order_history")) {
            orderHistory.clear();
            for (int i = 0; i < json["order_history"].GetArray().Size(); i++) {
                rapidjson::Document doc;
                doc.CopyFrom(json["order_history"][i], json.GetAllocator());
                Order order(doc);
                orderHistory.push_back(order);
            }
        }

        if (json.HasMember("passenger_id") && json["passenger_id"].IsInt())
            id = json["passenger_id"].GetInt();
    }

    void patch(rapidjson::Document& json) {
        validate_json(json, false);
        if (json.HasMember("name"))
            name = json["name"].GetString();
        if (json.HasMember("rating"))
            rating = json["rating"].GetDouble();

        if (json.HasMember("pinned_addresses")) {
            pinnedAddresses.clear();
            for (const auto& address : json["pinned_addresses"].GetArray()) {
                string address_str = address.GetString();
                GEOAddress geoAddress(address_str);
                pinnedAddresses.push_back(geoAddress);
            }
        }

        if (json.HasMember("payment_method")) {
            string payment_str = json["payment_method"].GetString();
            string payment = is_correct_payment(payment_str);
            if (payment == "cash")
                paymentMethod = PaymentMethod::CASH;
            else if (payment == "online")
                paymentMethod = PaymentMethod::ONLINE;
            else if (payment == "bank_bill" || payment == "bank bill")
                paymentMethod = PaymentMethod::BANK_BILL;
        }

        if (json.HasMember("order_history")) {
            orderHistory.clear();
            for (int i = 0; i < json["order_history"].GetArray().Size(); i++) {
                rapidjson::Document doc;
                doc.CopyFrom(json["order_history"][i], json.GetAllocator());
                Order order(doc);
                orderHistory.push_back(order);
            }
        }
    }

    /**
     * Validates the data from json file.
     * @param json - json file with passenger's data.
     * @param is_creation - flag for checking JSON-file while creating of passenger.
     */
    void validate_json(rapidjson::Document& json, bool is_creation=true) {
        IncorrectDataException exc;

        if (is_creation && !json.HasMember("name"))
            exc.addEntry("name", "Passenger: Body does not have parameter 'name'");
        else if (json.HasMember("name")) {
            if (!json["name"].IsString())
                exc.addEntry("name", "Passenger: Parameter 'name' is incorrect, expected type: 'string'");
            else {
                string check = json["name"].GetString();
                if (check.empty())
                    exc.addEntry("name",
                                 "Passenger: Parameter 'name' is incorrect, name should contain minimum 1 letter");
                for (char &c : check) {
                    if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ' && c != '-') {
                        exc.addEntry("name", "Passenger: Parameter 'name' is incorrect,"
                                             " name should not contain any characters except letters");
                        break;
                    }
                }
            }
        }

        if (is_creation && !json.HasMember("rating"))
            exc.addEntry("rating", "Passenger: Body does not have parameter 'rating'");
        else if (json.HasMember("rating")) {
            if (!json["rating"].IsNumber())
                exc.addEntry("rating", "Passenger: Parameter 'rating' is incorrect, expected type: 'number'");
            else {
                float check = json["rating"].GetDouble();
                if (check < 0.0 || check > 5.0)
                    exc.addEntry("rating",
                                 "Passenger: Parameter 'rating' is out of range, expected: 0 <= value <= 5.0, but given: " +
                                 to_string(check));
            }
        }

        if (is_creation && !json.HasMember("payment_method"))
            exc.addEntry("payment_method", "Passenger: Body does not have parameter 'payment_method'");
        else if (json.HasMember("payment_method")) {
            if (!json["payment_method"].IsString())
                exc.addEntry("payment_method",
                             "Passenger: Parameter 'payment_method' is incorrect, expected type: 'string'");
            else {
                string check = json["payment_method"].GetString();
                try {
                    is_correct_payment(check);
                } catch (IncorrectDataException) {
                    exc.addEntry("payment_method",
                                 "Passenger: Parameter 'payment_method' is incorrect, "
                                 "expected: 'cash', 'online', 'bank_bill', but given: " + check);
                }
            }
        }

        if (is_creation && !json.HasMember("pinned_addresses"))
            exc.addEntry("pinned_addresses", "Passenger: Body does not have parameter 'pinned_addresses'");
        else if (json.HasMember("pinned_addresses")) {
            if (!json["pinned_addresses"].IsArray())
                exc.addEntry("pinned_addresses",
                             "Passenger: Parameter 'pinned_addresses' is incorrect, expected type: 'array'");
            else {
                for (const auto &point : json["pinned_addresses"].GetArray()) {
                    if (!point.IsString()) {
                        exc.addEntry("pinned_addresses",
                                     "Passenger: Elements of the parameter 'pinned_addresses' are incorrect, expected type: 'string'");
                        break;
                    }
                    string address = point.GetString();
                    if (!GEOAddress::is_correct_address(address)) {
                        exc.addEntry("pinned_addresses",
                                     "Passenger: Elements of the parameter 'pinned_addresses' are incorrect, expected example: '+40.75-74.00'"
                                     ", but given: " + address);
                        break;
                    }
                }
            }
        }

        if (json.HasMember("passenger_id") && !json["passenger_id"].IsInt())
            exc.addEntry("passenger_id", "Passenger: Parameter 'passenger_id' is incorrect, expected type: 'integer'");
        else if (json.HasMember("passenger_id") && json["passenger_id"].IsInt()) {
            int driver_id = json["passenger_id"].GetInt();
            if (driver_id < 0)
                exc.addEntry("passenger_id",
                             "Passenger: Parameter 'passenger_id' is incorrect, expected: positive integer"
                             ", but given: " + to_string(driver_id));
        }

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());
    }

    /**
     * Checks the validity of payment method and return the string in the lowercase if the payment method is correct,
     *  otherwise - null pointer.
     * @param payment - string is represented payment method of the passenger.
     * @return If the payment method is correct => string (in lowercase) that represents the payment method,
     *  otherwise => throw an exception.
     */
    string is_correct_payment(string& payment) {
        string str = payment;
        for (char &c : str) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ')
                throw IncorrectDataException();
        }
        if (str == "cash" || str == "online" || str == "bank_bill" || str == "bank bill")
            return str.c_str();
        throw IncorrectDataException();
    }

    string to_json_string() {
        string res = "{\n";
        res += "passenger_id: " + std::to_string(id) + ",\n";
        res += "name: " + name + ",\n";
        res += "rating: " + std::to_string(rating) + ",\n";
        res += "payment_method: ";
        if (paymentMethod == PaymentMethod::CASH)
            res += "cash,\n";
        else if (paymentMethod == PaymentMethod::ONLINE)
            res += "online,\n";
        else if (paymentMethod == PaymentMethod::BANK_BILL)
            res += "bank_bill,\n";
        res += "pinned_addresses: [\n";
        for (int i = 0; i < pinnedAddresses.size() - 1; i++) {
            res += pinnedAddresses[i].geoString() + ",\n";
        }
        if (!pinnedAddresses.empty())
            res += pinnedAddresses[pinnedAddresses.size() - 1].geoString() + "\n";
        res += "]\n}";
        return res;
    }

    bool operator==(const Passenger& obj) {
        if (name == obj.name && rating == obj.rating && paymentMethod == obj.paymentMethod
                && orderHistory.size() == obj.orderHistory.size()
                && pinnedAddresses.size() == obj.pinnedAddresses.size()) {
            for (int i = 0; i < orderHistory.size(); i++) {
                if (orderHistory[i] != obj.orderHistory[i])
                    return false;
            }
            for (int i = 0; i < pinnedAddresses.size(); i++) {
                if (pinnedAddresses[i] != obj.pinnedAddresses[i])
                    return false;
            }
            return true;
        }
        return false;
    }

    float getRating() const {
        return rating;
    }

    const vector<Order> &getOrderHistory() const {
        return orderHistory;
    }

    const vector<GEOAddress> &getPinnedAddresses() const {
        return pinnedAddresses;
    }

    PaymentMethod getPaymentMethod() const {
        return paymentMethod;
    }
};


#endif //PSS_PASSENGER_H
