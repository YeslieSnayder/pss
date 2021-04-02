//
// Created by yesliesnayder on 02.04.2021.
//

#include "pistache/endpoint.h"

using namespace Pistache;
using namespace std;

struct HelloHandler : public Http::Handler {
HTTP_PROTOTYPE(HelloHandler)
    virtual void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        if (request.resource() == "/doc" && request.method() == Http::Method::Post) {
            response.headers()
                    .add<Http::Header::Server>("Homie")
                    .add<Http::Header::ContentType>(MIME(Text, Plain));
            auto stream = response.stream(Http::Code::Ok);
            stream << "Yeah...\n" << Http::ends;
        } else {
            response.headers()
                    .add<Http::Header::Server>("Homee")
                    .add<Http::Header::ContentType>(MIME(Text, Plain));
            auto stream = response.stream(Http::Code::Bad_Request);
            stream << "Sorry, but your request is incorrect\n" << Http::ends;
        }
    }
};

int main() {
    Address addr(Ipv4::any(), Port(9080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());

    cout << "Server connected to " << addr.host() << ":" << addr.port() << endl;
    server.serve();
}