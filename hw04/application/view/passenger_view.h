//
// Created by yesliesnayder on 06.04.2021.
//

#ifndef PSS_PASSENGER_VIEW_H
#define PSS_PASSENGER_VIEW_H

#include <vector>
#include <iostream>

using namespace std;

class PassengerView {
public:
    string loginPassenger(unsigned long int id) {
        return "{id: " + to_string(id) + "}";
    }

    string sendBadRequestError(vector<string> badFields, vector<string> description) {
        string res = "{";
        for (int i = 0; i < badFields.size() - 1; i++) {
            res += badFields[i] + ": " + description[i] + ", ";
        }
        res += badFields[badFields.size()-1] + ": " + description[description.size()-1] + "}";
        return res;
    }
};

#endif //PSS_PASSENGER_VIEW_H
