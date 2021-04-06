//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGER_H
#define PSS_PASSENGER_H

#include <vector>
#include "Order.h"
#include "Address.h"

using namespace std;

enum class PAYMENT_METHOD {
    CASH,
    ONLINE,
    BANK_BILL
};

class Passenger {
    string name;
    float rating;   // 0.0 <= value <= 5.0
    vector<Order> orderHistory;
    vector<GEOAddress> pinnedAddresses;
    PAYMENT_METHOD paymentMethod;

public:
    Passenger() = default;
};


#endif //PSS_PASSENGER_H
