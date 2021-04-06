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

    string loginBadRequest(vector<string> badFields, vector<string> description) {
        string res = "{";
        for (int i = 0; i < badFields.size() - 1; i++) {
            res += badFields[i] + ": " + description[i] + ", ";
        }
        res += badFields[badFields.size()-1] + ": " + description[description.size()-1] + "}";
        return res;
    }

    /**
     * Logging of the message to a log-file.
     * @param message - information that will be written to the log-file.
     */
    void log(string message) {
        cout << message << endl;
    }
};

#endif //PSS_PASSENGER_VIEW_H
