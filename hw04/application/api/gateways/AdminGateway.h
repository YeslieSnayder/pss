//
// Created by yesliesnayder on 17.04.2021.
//

#ifndef PSS_ADMINGATEWAY_H
#define PSS_ADMINGATEWAY_H

#include "pistache/endpoint.h"
#include "../config.h"

#include "../../model/model.h"
#include "../../view/admin_view.h"
#include "../../model/objects/Admin.h"

using namespace Pistache;


class AdminGateway {
    static inline AdminView view;

public:

    /**
     * PUT /admin
     * The method is responsible to login into the system by admin. This method is idempotent,
     * for each call of this method it will return same result.
     * @param request - request from app.
     * @param response - Created (201) => admin was created,
     * Bad request (400) => request contains bad data,
     * Forbidden (403) => incorrect password.
     */
    static void loginAdmin(const Rest::Request& request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Put, true);
            Document json;
            json.Parse(request.body().c_str());

            unsigned long int id = Model::createAdmin(json);
            view.sendAdminCreated(id, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * POST /admin
     * Returns the information about admin with data from input (email and password).
     * @param request - request from app.
     * @param response - Ok (200) => the data was correct -> returns data of the admin,
     * Bad request (400) => request contains bad data,
     * Forbidden (403) => incorrect password,
     * Not Found (404) => the admin wasn't found.
     */
    static void getAdmin(const Rest::Request& request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(request.body().c_str());

            Admin* admin = Model::getAdmin(json);
            view.sendAdminData(*admin, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
    }

    /**
     * POST /admin/info
     * Returns the information for admin according to data from request.
     * @param request - request from app.
     * @param response - Ok (200) => the data was correct -> returns information for the admin,
     * Bad request (400) => request contains bad data,
     * Forbidden (403) => incorrect password,
     * Not Found (404) => the admin wasn't found.
     */
    static void getInfo(const Rest::Request& request, Http::ResponseWriter response) {
        response.headers()
                .add<Http::Header::Server>(SERVER_NAME)
                .add<Http::Header::ContentType>(MIME(Application, Json));

        try {
            checkRequest(request, Http::Method::Post, true);
            Document json;
            json.Parse(request.body().c_str());

            string info = Model::getInfoAdmin(json);
            view.sendInfo(info, response);

        } catch (IncorrectDataException e) {
            view.sendBadRequest(e.getErrors(), response);
        } catch (NotFoundException e) {
            view.sendNotFound(e.getMessage(), response);
        } catch (ForbiddenException e) {
            view.sendForbidden(e.getMessage(), response);
        }
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


#endif //PSS_ADMINGATEWAY_H
