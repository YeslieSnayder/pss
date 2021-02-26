//
// Created by yesliesnayder on 25.02.2021.
//


#ifndef PSS_LOGGER_H
#define PSS_LOGGER_H


#include <string>
#include <iostream>

static void log(const std::string& msg) {
    std::cout << msg << std::endl;
}

static void log(bool isError, const std::string& msg) {
    std::cout << (isError ? "Permission denied: " : "Success: ") << msg << std::endl;
}


#endif //PSS_LOGGER_H