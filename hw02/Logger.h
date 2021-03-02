//
// Created by Andrey Kuzmickiy group BS20-03.
//


#ifndef PSS_LOGGER_H
#define PSS_LOGGER_H


#include <string>
#include <iostream>

enum Type {
    INFO,
    WARNING,
    ERROR
};

static void log(const std::string& msg) {
    std::cout << msg << std::endl;
}

static void log(Type type, const std::string& msg) {
    std::string head;
    if (type == INFO)
        head = "INFO: ";
    else if (type == WARNING)
        head = "WARNING: ";
    else if (type == ERROR)
        head = "ERROR: ";
    std::cout << head << msg << std::endl;
}


#endif //PSS_LOGGER_H