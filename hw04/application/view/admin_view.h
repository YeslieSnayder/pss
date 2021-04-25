//
// Created by yesliesnayder on 17.04.2021.
//

#ifndef PSS_ADMIN_VIEW_H
#define PSS_ADMIN_VIEW_H

#include <utility>
#include <vector>

#include "../model/objects/Admin.h"
#include "../model/exceptions/IncorrectDataException.h"
#include "../api/gateways/BaseGateway.h"

using namespace std;
using namespace Pistache;

class AdminView {
public:
    void sendBadRequest(const vector<IncorrectDataException::Entry>& errors, Http::ResponseWriter& response) {
        string res = "{";
        for (int i = 0; i < errors.size() - 1; i++) {
            res += errors[i].key + ": " + errors[i].value + ",";
        }
        if (!errors.empty())
            res += errors[errors.size()-1].key + ": " + errors[errors.size()-1].value;
        res += "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Bad_Request, res);
    }

    void sendNotFound(string message, Http::ResponseWriter& response) {
        string res = "{validation_error: {id: " + message + "}}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Not_Found, res);
    }

    void sendForbidden(string message, Http::ResponseWriter& response) {
        string res = "{permission_denied: " + message + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Forbidden, res);
    }

    void sendAdminCreated(unsigned long admin_id, Http::ResponseWriter& response) {
        string res = "{id: " + to_string(admin_id) + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Created, res);
    }

    void sendAdminData(Admin& admin, Http::ResponseWriter& response) {
        string res = "{";
        res += "admin_id: " + to_string(admin.getId()) + ",";
        res += "name: " + admin.getName() + ",";
        res += "email: " + admin.getEmail() + ",";
        res += "password: " + admin.getPassword() + "}";
        res = BaseGateway::convert_to_right_json(res);
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendInfo(string json, Http::ResponseWriter& response) {
        string res = BaseGateway::convert_to_right_json(std::move(json));
        response.send(Pistache::Http::Code::Ok, res);
    }
};


#endif //PSS_ADMIN_VIEW_H
