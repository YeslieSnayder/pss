//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "pistache/router.h"
#include "pistache/endpoint.h"

#include "gateways/DriverGateway.h"
#include "gateways/PassengerGateway.h"

#include "../db/TestDatabase.h"

using namespace Pistache;
using namespace std;


/**
 * Initialization of all routes that are available in server.
 * @return Object that contains all routes.
 */
Rest::Router initRouter() {
    Rest::Router router;
//    Rest::Routes::Get(router, "/users/all", Rest::Routes::bind(&UsersApi::getAllUsers));
//    Rest::Routes::Post(router, "/passengers/:id", Rest::Routes::bind(&PassengerGateway::getPassenger));
//    Rest::Routes::Post(router, "/driver/:id", Rest::Routes::bind(&DriverGateway::getDriver));
//    Rest::Routes::Get(router, "/link/*/to/*", Rest::Routes::bind(&UsersApi::linkUsers));

    // Passenger
    Rest::Routes::Put(router, "/passengers", Rest::Routes::bind(&PassengerGateway::loginPassenger));
    Rest::Routes::Get(router, "/passengers/:id", Rest::Routes::bind(&PassengerGateway::getPassenger));
    Rest::Routes::Patch(router, "/passengers/:id", Rest::Routes::bind(&PassengerGateway::updatePassenger));
    Rest::Routes::Post(router, "/passengers/assign/:id", Rest::Routes::bind(&PassengerGateway::assignRide));
    Rest::Routes::Post(router, "/passengers/order/:id", Rest::Routes::bind(&PassengerGateway::orderRide));
    Rest::Routes::Get(router, "/passengers/car/:id", Rest::Routes::bind(&PassengerGateway::getCarInfo));
    Rest::Routes::Get(router, "/passengers/order/:id", Rest::Routes::bind(&PassengerGateway::getOrderInfo));

    // Driver


    return router;
}

/**
 * Initialization and running server.
 * @param host - address where server will be running.
 */
void runServer(Pistache::Address host) {
    auto opts = Http::Endpoint::options().threads(1);

    Http::Endpoint server(host);
    server.init(opts);
    server.setHandler(initRouter().handler());

    cout << "Server connected to " << host.host() << ":" << host.port() << endl;
    server.serve();
}

int main() {
    runServer(Pistache::Address(Ipv4::any(), Port(9080)));
}