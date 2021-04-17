//
// Created by yesliesnayder on 16.04.2021.
//

#ifndef PSS_ADMIN_H
#define PSS_ADMIN_H

#include "rapidjson/document.h"
#include "User.h"

using namespace Pistache;

class Admin : public User {
    string email;
    string password;

public:
    Admin(unsigned long id, string& name, string& email, string& password) : email(email), password(password) {
        Admin::id = id;
        Admin::name = std::move(name);
    }

    Admin(rapidjson::Document& json) {
        validate_json(json);
        name = json["name"].GetString();
        email = json["email"].GetString();
        password = json["password"].GetString();
    }

    void validate_json(rapidjson::Document& json, bool is_creation=true) {
        IncorrectDataException exc;

        if (is_creation && !json.HasMember("name"))
            exc.addEntry("name", "Admin: Body does not have parameter 'name'");
        else if (json.HasMember("name")) {
            if (!json["name"].IsString())
                exc.addEntry("name", "Admin: Parameter 'name' is incorrect, expected type: 'string'");
            else {
                string check = json["name"].GetString();
                if (check.empty())
                    exc.addEntry("name", "Admin: Parameter 'name' is incorrect, name should contain minimum 1 letter");
                for (char &c : check) {
                    if ((c < 'A' || c > 'Z' && c < 'a' || c > 'z') && c != '_' && c != ' ' && c != '-') {
                        exc.addEntry("name", "Admin: Parameter 'name' is incorrect,"
                                             " name should not contain any characters except letters");
                        break;
                    }
                }
            }
        }

        if (is_creation && !json.HasMember("email"))
            exc.addEntry("email", "Admin: Body does not have parameter 'email'");
        else if (json.HasMember("email")) {
            if (!json["email"].IsString())
                exc.addEntry("email", "Admin: Parameter 'email' is incorrect, expected type: 'string'");
            else {
                string check = json["email"].GetString();
                if (check.empty())
                    exc.addEntry("email", "Admin: Parameter 'email' is incorrect, email should contain minimum 1 letter");
            }
        }

        if (is_creation && !json.HasMember("password"))
            exc.addEntry("password", "Admin: Body does not have parameter 'password'");
        else if (json.HasMember("password")) {
            if (!json["password"].IsString())
                exc.addEntry("password", "Admin: Parameter 'password' is incorrect, expected type: 'string'");
            else {
                string check = json["password"].GetString();
                if (check.empty())
                    exc.addEntry("password", "Admin: Parameter 'password' is incorrect, name should contain minimum 1 letter");
            }
        }

        if (exc.hasErrors())
            throw IncorrectDataException(exc.getErrors());
    }

    string to_json_string() {
        string res = "{\n";
        res += "admin_id: " + to_string(id) + ",\n";
        res += "name: " + name + ",\n";
        res += "email: " + email + "\n}";
    }

    bool operator==(const Admin& other) {
        return id == other.id && name == other.name && password == other.password;
    }

    static bool compare_password(string pas1, string pas2) {
        return pas1 != pas2;
    }

    const string &getEmail() const {
        return email;
    }

    const string &getPassword() const {
        return password;
    }

    void setEmail(const string &email) {
        Admin::email = email;
    }

    void setPassword(const string &password) {
        Admin::password = password;
    }
};


#endif //PSS_ADMIN_H
