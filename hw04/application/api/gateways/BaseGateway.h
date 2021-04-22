//
// Created by yesliesnayder on 23.04.2021.
//

#ifndef PSS_BASEGATEWAY_H
#define PSS_BASEGATEWAY_H

#include "pistache/endpoint.h"

using namespace Pistache;

class BaseGateway {
    static string get_json_value(string value) {
        char t = value[value.size()-1];
        while (t == ' ') {
            value.pop_back();
            t = value[value.size()-1];
        }
        bool is_not_number = false;
        bool has_dot = false;
        bool has_sign = (value[0] == '-' || value[0] == '+');
        for (int i = (has_sign) ? 1 : 0; i < value.size(); i++) {
            char& n = value[i];
            if (n == '.' && !has_dot)
                has_dot = true;
            else if (n == '.' && has_dot || !isdigit(n)) {
                is_not_number = true;
                break;
            }
        }
        return (is_not_number && value != "true" && value != "false") ? "\"" + value + "\"" : value;
    }

public:
    static string convert_to_right_json(string json_str) {
        string correct_json;
        string value;

        bool is_key = false, is_value = false;
        for (int i = 0; i < json_str.size(); i++) {
            char &c = json_str[i];

            if (c == '{') {
                string s_obj;
                char t = c;
                int count = i, braces_num = 1;
                while (t != '}' || braces_num != 0) {
                    t = json_str[++count];
                    if (t == '{' || t == '[') braces_num++;
                    else if (t == '}' || t == ']') braces_num--;
                    s_obj += t;
                }
                s_obj.pop_back();
                correct_json += "{" + convert_to_right_json(s_obj) + "}";
                i = count;
                is_key = false;
                is_value = true;
                value.clear();
                continue;
            } else if (c == '[') {
                string s_arr;
                char t = c;
                int count = i, braces_num = 1;
                while (t != ']' || braces_num != 0) {
                    t = json_str[++count];
                    if (t == '{' || t == '[') braces_num++;
                    else if (t == '}' || t == ']') braces_num--;
                    s_arr += t;
                }
                s_arr.pop_back();
                correct_json += "[" + convert_to_right_json(s_arr) + "]";
                i = count;
                is_key = false;
                is_value = true;
                value.clear();
                continue;
            }

            if (isspace(c) && (!is_key && !is_value || is_key && is_value)) continue;
            else if (!is_key && !is_value) {    // key begin
                is_key = true;
                correct_json += '\"';
            } else if (is_key && c == ':') {    // key end
                char t = correct_json[correct_json.size() - 1];
                while (t == ' ') {
                    correct_json.pop_back();
                    t = correct_json[correct_json.size() - 1];
                }
                correct_json += '\"';
                is_value = true;
            } else if (is_value && c != ',') {  // value begin
                value += c;
                is_key = false;
                continue;
            } else if (is_value && c == ',') {  // value end
                correct_json += get_json_value(value);
                value.clear();
                is_value = false;
            }

            correct_json += c;
        }
        if (!value.empty()) {
            correct_json += get_json_value(value);
            value.clear();
        }
        return correct_json;
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


#endif //PSS_BASEGATEWAY_H
