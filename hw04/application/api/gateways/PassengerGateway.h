//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_PASSENGERGATEWAY_H
#define PSS_PASSENGERGATEWAY_H

#include "pistache/endpoint.h"

#include "../../model/model.h"
#include "../../model/objects/Passenger.h"
#include "../../view/passenger_view.h"

using namespace Pistache;

class PassengerGateway {
    Model model;
    PassengerView view;

public:
    PassengerGateway(Model model, PassengerView view) : model(model), view(view) {}

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
        try {
            checkRequest(request, Http::Method::Put, true);
            unsigned long int id = model.
            string ans = view.loginPassenger(id);
        } catch (exception e) {

        }
    }

    static void getPassenger(const Rest::Request &request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        string body = "This is passenger with id = " + id;
        response.headers()
                .add<Http::Header::Server>("Passenger")
                .add<Http::Header::ContentType>(MIME(Text, Plain));
        auto stream = response.stream(Http::Code::Ok);
        stream << body << Http::ends;
    }

    static void checkRequest(const Rest::Request &request, Http::Method method, bool requireBody=false) {
        if (request.method() != method)
            throw invalid_argument("Request method is incorrect");
        if (requireBody && request.body().empty())
            throw invalid_argument("Body is empty");
    }
};


#endif //PSS_PASSENGERGATEWAY_H
