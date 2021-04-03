//
// Created by yesliesnayder on 03.04.2021.
//

#include "pistache/endpoint.h"
#include "../config.h"
#include "DriverGateway.h"
#include "PassengerGateway.h"

using namespace Pistache;

struct MainHandler : public Http::Handler {
    HTTP_PROTOTYPE(MainHandler)

    virtual void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        // PASSENGERS
        if (request.resource() == "/passenger" && request.method() == Http::Method::Post) {
            response.headers()
                    .add<Http::Header::Server>(SERVER_NAME)
                    .add<Http::Header::ContentType>(MIME(Text, Plain));
            auto stream = response.stream(Http::Code::Ok);
            stream << "Passengers\n" << Http::ends;
        }

        // DRIVERS
        else if (request.resource() == "/driver" && request.method() == Http::Method::Get) {
            response.headers()
                    .add<Http::Header::Server>(SERVER_NAME)
                    .add<Http::Header::ContentType>(MIME(Text, Plain));
            auto stream = response.stream(Http::Code::Ok);
            stream << "Drivers\n" << Http::ends;
        }

        // BAD REQUEST
        else {
            response.headers()
                    .add<Http::Header::Server>(SERVER_NAME)
                    .add<Http::Header::ContentType>(MIME(Text, Plain));
            auto stream = response.stream(Http::Code::Bad_Request);
            stream << "Sorry, but your request is incorrect\n" << Http::ends;
        }
    }
};