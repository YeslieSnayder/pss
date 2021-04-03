//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGER_H
#define PSS_PASSENGER_H

#include <vector>
#include "Order.h"
#include "Address.h"

using namespace std;

class Passenger {
    string name;
    float rating;
    vector<Order> orderHistory;
    vector<Address> pinnedAddresses;

    enum payment_method{CASH, ONLINE, BANK_BILL};

};


#endif //PSS_PASSENGER_H
