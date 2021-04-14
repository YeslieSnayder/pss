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
     * PUT /passengers
     * The method allows user to login into the system. This method is idempotent,
     * for each call of this method it will return same result.
     * @param request - request from app.
     * @param response - The response to the passenger.
     */
    static void loginPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Put, true);

            Document json;
            json.Parse(request.body().c_str());
            unsigned long int id = Model::createPassenger(json);
            view.sendIdOK(id, response);

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        }
    }

    /**
     * GET /passengers/:id
     * The method returns the information about the passenger with given id.
     * @param request
     * @param response
     */
    static void getPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Text, Plain));

        try {
            checkRequest(request, Http::Method::Get);
            Document json;
            json.Parse(request.body().c_str());
            Passenger* passenger = Model::getPassenger(json);
            if (passenger == nullptr)
                throw invalid_argument("Passenger with given id(" + to_string(id) + ") doesn't exist");
            view.sendPassengerData(*passenger, response);

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        }
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
