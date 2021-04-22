//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGERGATEWAY_H
#define PSS_PASSENGERGATEWAY_H

#include "pistache/endpoint.h"
#include "../config.h"

#include "BaseGateway.h"
#include "../../model/model.h"
#include "../../view/passenger_view.h"
#include "../../model/objects/Passenger.h"

using namespace Pistache;

class PassengerGateway : public BaseGateway {
    static inline PassengerView view;
public:

    /**
     * PUT /passengers
     * The method allows user to login into the system. This method is idempotent,
     * for each call of this method it will return same result.
     * @param request - request from app.
     * @param response - Created (201) => passenger was created,
     * Bad request (400) => request contains bad data,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void loginPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Put, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            unsigned long int id = Model::createPassenger(json);
            Passenger* passenger = Model::getPassenger(id);
            view.sendPassengerData(*passenger, response);
            delete passenger;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * GET /passengers/:id
     * The method returns the information about the passenger with given id.
     * @param request - contains id of the passenger (in a header).
     * @param response - OK (200) => if passenger exists,
     * Bad request (400) => if request contains bad data,
     * Not found (404) => passenger with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            Passenger* passenger = Model::getPassenger(id);
            if (passenger == nullptr)
                throw invalid_argument("Passenger with given id(" + to_string(id) + ") doesn't exist");
            view.sendPassengerData(*passenger, response);
            delete passenger;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * PATCH /passengers/:id
     * The method changes data of passenger with id from input.
     * @param request - new data of a passenger.
     * @param response - OK (200) => if passenger have been changed,
     * Bad request (400) => if request contains bad data,
     * Not found (404) => passenger with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void updatePassenger(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Patch, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            Passenger* passenger = Model::patchPassenger(id, json);
            if (passenger == nullptr)
                throw invalid_argument("Passenger with given id(" + to_string(id) + ") doesn't exist");
            view.sendPassengerData(*passenger, response);
            delete passenger;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * POST /passengers/assign/:id
     * Returns information about a ride with data from passenger.
     * @param request - contains start and end points and preferred car.
     * @param response - OK (200) => returns information about the order (price, distance and time),
     * Bad Request (400) => request contains bad data,
     * Not found (404) => passenger with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void assignRide(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            PreOrder* order = Model::assignOrder(id, json);
            if (order == nullptr)
                throw invalid_argument("Order was incorrect");
            view.sendPreOrderData(*order, response);
            delete order;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * POST /passengers/order/:id
     * Order the ride. Require: call assignRide before this method.
     * The method returns full information about the order.
     * @param request - The information about order (can be without driver_id).
     * @param response - OK (200) => if the order was correct,
     * Bad request (400) => if request contains bad data,
     * Not found (404) => driver or passenger with given data doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void orderRide(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            Order* order = Model::assignAndOrderRide(id, json);
            if (order == nullptr)
                throw invalid_argument("Order was incorrect");
            view.sendOrderData(*order, response);
            delete order;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * POST /passengers/car/:id
     * Returns information about the car with given number.
     * @param request - contains the number of a car.
     * @param response - OK (200) => if car exists,
     * Bad request (400) => if request contains bad data,
     * Not found (404) => the car with given data doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getCarInfo(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            Car* car = Model::getCarForPassenger(id, json);
            if (car == nullptr)
                throw invalid_argument("Information of the car was incorrect");
            view.sendCarInfo(*car, response);
            delete car;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * GET /passengers/order/:order_id
     * Returns the information about order with given id.
     * @param request - empty body. Header contains id of the order.
     * @param response - OK (200) => the order exists,
     * Not found (404) => the order doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getOrderInfo(const Rest::Request &request, Http::ResponseWriter response) {
        auto order_id = request.param(":order_id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            Order* order = Model::getOrder(order_id);
            if (order == nullptr)
                throw invalid_argument("Information of the car was incorrect");
            view.sendOrderData(*order, response);
            delete order;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * GET /passengers/:id/orders
     * Returns order history of the passenger.
     * @param request - Body is empty. Header contains id of the passenger.
     * @param response - OK (200) with order history,
     * Not found (404) => if passenger with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getOrderHistory(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            vector<Order> history = Model::getPassengerOrderHistory(id);
            view.sendOrderHistory(history, response);

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }
};


#endif //PSS_PASSENGERGATEWAY_H
