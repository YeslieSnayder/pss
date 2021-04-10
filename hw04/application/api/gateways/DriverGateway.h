//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVERGATEWAY_H
#define PSS_DRIVERGATEWAY_H

#include "pistache/endpoint.h"
#include "../config.h"

#include "../../model/objects/Driver.h"
#include "../../model/model.h"
#include "../../view/driver_view.h"

using namespace Pistache;


class DriverGateway {
public:

    // PUT /drivers
    static void loginDriver(const Rest::Request& request, Http::ResponseWriter response) {
        // TODO: login the driver
    }

    // GET /drivers/:id
    static void getDriver(const Rest::Request& request, Http::ResponseWriter response) {
        // TODO: Return complete info about driver

        auto id = request.param(":id").as<int>();
        string body = "This is driver with id = " + id;
        response.send(Http::Code::Ok, body);
    }

    // PATCH /drivers/:id
    static void updateDriver(const Rest::Request& request, Http::ResponseWriter response) {
        // TODO: Update driver from JSON file (body)
    }

    // GET /drivers/:id/orders
    static void getOrderHistory(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Return order history
    }

    // GET /drivers/:id/car
    static void getCarInfo(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Return information about the car
    }

    // GET /drivers/order
    static void checkAvailableOrders(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Allows driver to check available orders (distance does not matter)
    }

    // POST /drivers/:id
    static void acceptOrder(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Accept the order (id of the order in the body of request)
    }

    // POST /drivers/complete
    static void completeOrder(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Complete the order
    }
};


#endif //PSS_DRIVERGATEWAY_H
