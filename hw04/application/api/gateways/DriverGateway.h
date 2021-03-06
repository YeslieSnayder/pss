//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_DRIVERGATEWAY_H
#define PSS_DRIVERGATEWAY_H

#include "pistache/endpoint.h"
#include "../config.h"

#include "BaseGateway.h"
#include "../../model/model.h"
#include "../../view/driver_view.h"
#include "../../model/objects/Driver.h"

using namespace Pistache;

class DriverGateway : public BaseGateway {
    static inline DriverView view;
public:

/**
     * PUT /drivers
     * The method allows user to login into the system. This method is idempotent,
     * for each call of this method it will return same result.
     * @param request - request from app.
     * @param response - Created (201) => driver was created,
     * Bad request (400) => request contains bad data,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void loginDriver(const Rest::Request& request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Put, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            unsigned long int id = Model::createDriver(json);
            Driver* driver = Model::getDriver(id);
            view.sendDriverData(*driver, response, Pistache::Http::Code::Created);
            delete driver;

        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        }
    }

    /**
     * GET /drivers/:id
     * The method returns the information about the driver with given id.
     * @param request - contains id of the driver (in a header).
     * @param response - OK (200) => if driver exists,
     * Bad request (400) => if request contains bad data,
     * Not found (404) => driver with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getDriver(const Rest::Request& request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            Driver* driver = Model::getDriver(id);
            if (driver == nullptr)
                throw invalid_argument("Driver with given id(" + to_string(id) + ") doesn't exist");
            view.sendDriverData(*driver, response);
            delete driver;

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }

    /**
     * PATCH /drivers/:id
     * The method changes data of driver with id from input.
     * @param request - new data of a driver.
     * @param response - OK (200) => if driver have been changed,
     * Bad request (400) => if request contains bad data,
     * Not found (404) => driver with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void updateDriver(const Rest::Request& request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Patch, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            Driver* driver = Model::patchDriver(id, json);
            if (driver == nullptr)
                throw invalid_argument("Driver with given id(" + to_string(id) + ") doesn't exist");
            view.sendDriverData(*driver, response);
            delete driver;

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }

    /**
     * GET /drivers/:id/orders
     * Returns order history of the driver.
     * @param request - Body is empty. Header contains id of the driver.
     * @param response - OK (200) with order history,
     * Not found (404) => if driver with given id doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getOrderHistory(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            vector<Order> history = Model::getDriverOrderHistory(id);
            view.sendListOrders(history, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }

    /**
     * GET /drivers/:id/car
     * Returns information about car of a driver with given id.
     * @param request - Body is empty. Header contains id of a driver.
     * @param response - OK (200) => if car exists,
     * Not found (404) => the car with given data doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void getCarInfo(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            vector<Car> cars = Model::getCars(id);
            if (cars.empty())
                throw invalid_argument("Information of the car was incorrect");
            view.sendCarInfo(cars, response);

        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }

    /**
     * GET /drivers/order
     * Returns the list of available orders (that have status: ready).
     * @param request - empty.
     * @param response - OK (200) with the list of orders,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void checkAvailableOrders(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Get);
            vector<Order> orders = Model::getAvailableOrders();
            view.sendListOrders(orders, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }

    /**
     * POST /drivers/:id
     * Used to accept the order. Usually, before the call of this method
     * driver should check all available orders to find the order_id.
     * @param request - contains id of the order.
     * @param response - OK (200) => returns full information about the order,
     * Bad Request (400) => request contains bad data,
     * Not found (404) => the order was assigned by other driver or not found in database,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void acceptOrder(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            Order* order = Model::acceptOrderByDriver(id, json);
            view.sendOrderData(*order, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }

    /**
     * POST /drivers/complete
     * Complete the order that was ordered before by that driver.
     * @param request - contains id of the order and complete time for it.
     * @param response - OK (200) => returns id of the completed order,
     * Bad Request (400) => request contains bad data,
     * Not found (404) => the order doesn't exist,
     * Forbidden (403) => this method is not allowed for this user.
     */
    static void completeOrder(const Rest::Request &request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(convert_to_right_json(request.body()).c_str());

            unsigned long int order_id = Model::completeOrder(json);
            view.sendOrderId(order_id, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        } catch (invalid_argument e) {
            string key("request_error");
            string value(e.what());
            view.sendBadRequest({{key, value}}, response);
        }
    }
};


#endif //PSS_DRIVERGATEWAY_H
