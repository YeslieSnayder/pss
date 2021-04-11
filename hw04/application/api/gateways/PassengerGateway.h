//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGERGATEWAY_H
#define PSS_PASSENGERGATEWAY_H

#include "pistache/endpoint.h"
#include "../config.h"

#include "../../model/model.h"
#include "../../model/objects/Passenger.h"
#include "../../view/passenger_view.h"
#include "../../view/logger.h"
#include "../../db/TestDatabase.h"

using namespace Pistache;

class PassengerGateway {
    static inline PassengerView view;

public:

    /**
     * The method allows user to login into the system. This method is idempotent,
     * for each call of this method it will return same result.
     * Example of request:
     * PUT "{
     *  passenger:
     *  {
     *      name: "Andrey"
     *      rating: 4.7
     *      payment_methods: ["ONLINE", "CASH"]
     *      pinned_addresses: ["+40.75-74.00", "+33.0+037.00"]
     *  }
     * }"
     * @param request
     * @param response - The response to the passenger.
     *
     * If request was correct and passenger's data satisfied all conditions, then returns
     * response with code 201 and id of the passenger:
     * HTTP 201 Created
     * "{
     *  id: 2
     * }"
     *
     * If request was incorrect or input data was incorrect, then returns
     * response with code 400 and fields with description of the problem:
     * HTTP 400 Bad Request
     * "{
     *  name: "Should be string"
     *  rating: "Is out of range, expected [0.0, 5.0], given -90.33"
     * }"
     */
    static void loginPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        string ans;
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Put, true);

            Document json;
            json.Parse(request.body().c_str());
            unsigned long int id = Model::createPassenger(json);
            ans = view.loginPassenger(id);

            auto res = response.send(Http::Code::Ok, ans);
            res.then([](ssize_t bytes) {
                log(LOG::INFO, "User was logged in");
            }, Async::Throw);

        } catch (exception e) {
            ans = view.sendBadRequestError({"name"}, {e.what()});

            auto res = response.send(Http::Code::Bad_Request, ans);
            res.then([](ssize_t bytes) {
                log(LOG::ERROR, "User wasn't logged in");
            }, Async::Throw);
        }
    }

    // GET /passengers/:id
    static void getPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Complete getting information about passenger (without full order history (last 3 orders))
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Text, Plain));
        string ans;

        try {
            checkRequest(request, Http::Method::Get);
            Document json;
            json.Parse(request.body().c_str());
            Passenger* passenger = Model::findPassenger(json);
            if (passenger == nullptr)
                throw invalid_argument("Passenger with given id(" + to_string(id) + ") doesn't exist");

        } catch (exception e) {
            ans = view.sendBadRequestError({"description"}, {e.what()});

            auto res = response.send(Http::Code::Bad_Request, ans);
            res.then([](ssize_t bytes) {
                log(LOG::ERROR, "User wasn't logged in");
            }, Async::Throw);
        }

        auto stream = response.stream(Http::Code::Ok);
        stream << "This is passenger with id = " << id << Http::ends;
    }

    // PATCH /passengers/:id
    static void updatePassenger(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Update passenger from JSON file (body)
    }

    // POST /passengers/assign/:id
    static void assignRide(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Return the information about accessible cars  (Same as orderRide)
    }

    // POST /passengers/order/:id
    static void orderRide(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Assign Driver and start the ride  (Same as assignRide)
    }

    // GET /passengers/car/:id
    static void getCarInfo(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Current coordinates of the assigned car (only if this passenger assigned the car)
    }

    // GET /passengers/order/:order_id
    static void getOrderInfo(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Return information about particular order that the passenger did
    }

    // GET /passengers/:id/orders
    static void getOrderHistory(const Rest::Request &request, Http::ResponseWriter response) {
        // TODO: Return order history
    }


    static void checkRequest(const Rest::Request &request, Http::Method method, bool requiredBody = false) {
        if (request.method() != method)
            throw invalid_argument("Request method is incorrect");
        if (requiredBody && request.headers().tryGet<Http::Header::ContentType>() == nullptr)
            throw invalid_argument("Content type has to be explicitly determine");
        if (requiredBody && request.body().empty())
            throw invalid_argument("Body is empty");
    }
};


#endif //PSS_PASSENGERGATEWAY_H
