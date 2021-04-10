//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGER_H
#define PSS_PASSENGER_H

#include <utility>
#include <vector>
#include "rapidjson/document.h"

#include "Order.h"
#include "Address.h"

using namespace std;

enum class PaymentMethod {
    CASH,
    ONLINE,
    BANK_BILL
};

class Passenger {
    unsigned long int id = NULL_ID;
    string name;
    float rating;
    vector<Order> orderHistory;
    vector<GEOAddress> pinnedAddresses;
    PaymentMethod paymentMethod;

public:
    static const unsigned long int NULL_ID = 0;

    Passenger(string name, float rating, const vector<Order> &orderHistory,
              const vector<GEOAddress> &pinnedAddresses, PaymentMethod paymentMethod) : name(std::move(name)),
                                                                                        rating(rating),
                                                                                        orderHistory(orderHistory),
                                                                                        pinnedAddresses(
                                                                                                 pinnedAddresses),
                                                                                        paymentMethod(paymentMethod) {}

    Passenger(const rapidjson::Document& json) {
        // TODO: create constructor
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

    unsigned long getId() const {
        return id;
    }

    const string &getName() const {
        return name;
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

    void setId(unsigned long id) {
        Passenger::id = id;
    }
};


#endif //PSS_PASSENGER_H
