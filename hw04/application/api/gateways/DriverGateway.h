//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVERGATEWAY_H
#define PSS_DRIVERGATEWAY_H

#include "pistache/endpoint.h"

#include "../../model/objects/Driver.h"

using namespace Pistache;


class DriverGateway {
public:
    static void getDriver(const Rest::Request& request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        string body = "This is driver with id = " + id;
        response.send(Http::Code::Ok, body);
    }
};


#endif //PSS_DRIVERGATEWAY_H
