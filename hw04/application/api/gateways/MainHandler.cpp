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

/*
    // 1. Parse a JSON string into DOM.
const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
Document d;
d.Parse(json);

    // 2. Modify it by DOM.
Value& s = d["stars"];
s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
StringBuffer buffer;
Writer<StringBuffer> writer(buffer);
d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
std::cout << buffer.GetString() << std::endl;
return 0;
 */

/*
 * Check existence of a field ("hello": string)
 *
Value::ConstMemberIterator itr = document.FindMember("hello");
if (itr != document.MemberEnd())
    printf("%s\n", itr->value.GetString());
 */

/*
 * Checking type of an object
 *
bool IsNumber()	N/A
bool IsUint()	unsigned GetUint()
bool IsInt()	int GetInt()
bool IsUint64()	uint64_t GetUint64()
bool IsInt64()	int64_t GetInt64()
bool IsDouble()	double GetDouble()
 */

/*
 * Assign an object
 *
Value contact(kObject);
contact.AddMember("name", "Milo", document.GetAllocator());
 */