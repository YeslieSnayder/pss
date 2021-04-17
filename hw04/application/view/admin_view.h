//
// Created by yesliesnayder on 17.04.2021.
//

#ifndef PSS_ADMIN_VIEW_H
#define PSS_ADMIN_VIEW_H

#include <vector>

#include "../model/objects/Admin.h"
#include "../model/exceptions/IncorrectDataException.h"

using namespace std;
using namespace Pistache;

class AdminView {
public:
    void sendBadRequest(const vector<IncorrectDataException::Entry>& errors, Http::ResponseWriter& response) {
        string res = "{\n";
        for (int i = 0; i < errors.size() - 1; i++) {
            res += errors[i].key + ": " + errors[i].value + ",\n";
        }
        res += errors[errors.size()-1].key + ": " + errors[errors.size()-1].value + "\n}";
        response.send(Pistache::Http::Code::Bad_Request, res);
    }

    void sendNotFound(string message, Http::ResponseWriter& response) {
        string res = "{\nvalidation_error: {\nid: " + message + "\n}\n}";
        response.send(Pistache::Http::Code::Not_Found, res);
    }

    void sendForbidden(string message, Http::ResponseWriter& response) {
        string res = "{\npermission_denied: " + message + "\n}";
        response.send(Pistache::Http::Code::Forbidden, res);
    }

    void sendAdminCreated(unsigned long admin_id, Http::ResponseWriter& response) {
        string res = "{\nid: " + to_string(admin_id) + "\n}";
        response.send(Pistache::Http::Code::Created, res);
    }

    void sendAdminData(Admin& admin, Http::ResponseWriter& response) {
        string res = "{\n";
        res += "admin_id: " + to_string(admin.getId()) + ",\n";
        res += "name: " + admin.getName() + ",\n";
        res += "email: " + admin.getEmail() + ",\n";
        res += "password: " + admin.getPassword() + "\n}";
        response.send(Pistache::Http::Code::Ok, res);
    }

    void sendInfo(string json, Http::ResponseWriter& response) {
        response.send(Pistache::Http::Code::Ok, json);
    }
};


#endif //PSS_ADMIN_VIEW_H
