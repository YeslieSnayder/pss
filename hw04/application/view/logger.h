//
// Created by yesliesnayder on 11.04.2021.
//

#include <iostream>

using namespace std;

#ifndef PSS_LOGGER_H
#define PSS_LOGGER_H

/**
 * The class represents the type of log message.
 */
enum class LOG {
    INFO, ERROR, DEBUG
};

/**
 * Write the message to the log with type from input.
 * @param type - the entity of enum LOG. Type of the log message.
 * @param message - information that will be written to the log.
 */
static void log(LOG type, string message) {
    switch (type) {
        case LOG::INFO:
            cout << "INFO: ";
            break;
        case LOG::DEBUG:
            cout << "DEBUG: ";
            break;
        case LOG::ERROR:
            cerr << "ERROR: " << message << endl;
            return;
        default:
            break;
    }
    cout << message << endl;
}

/**
 * Write the message to the log with tag (INFO).
 * @param message - information that will be written to the log.
 */
static void log(string message) {
    log(LOG::INFO, message);
}

#endif //PSS_LOGGER_H
