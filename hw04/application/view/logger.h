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
void log(LOG type, string message) {
    switch (type) {
        LOG::INFO: cout << "INFO: "; break;
        LOG::DEBUG: cout << "DEBUG: "; break;
        LOG::ERROR: cout << "ERROR: "; break;
        default: break;
    }
    cout << message << endl;
}

/**
 * Write the message to the log with tag (INFO).
 * @param message - information that will be written to the log.
 */
void log(string message) {
    log(LOG::INFO, message);
}

#endif //PSS_LOGGER_H
