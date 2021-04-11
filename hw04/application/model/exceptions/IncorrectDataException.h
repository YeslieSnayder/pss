//
// Created by yesliesnayder on 11.04.2021.
//

#include <vector>

#ifndef PSS_INCORRECTDATAEXCEPTION_H
#define PSS_INCORRECTDATAEXCEPTION_H


class IncorrectDataException : std::exception {
    struct Entry {
        std::string key;
        std::string value;
    };
    std::vector<Entry> errors{};

public:
    IncorrectDataException() = default;
    IncorrectDataException(std::string key, std::string value) {
        addEntry(key, value);
    }

    void addEntry(std::string key, std::string value) {
        errors.push_back({key, value});
    }

    virtual std::vector<Entry> getErrors() const {
        return errors;
    }

    virtual bool hasErrors() const {
        return !errors.empty();
    }

    virtual const char* what() const noexcept {
        std::string res = "{";
        for (int i = 0; i < errors.size() - 1; i++)
            res += errors[i].key + ": " + errors[i].value + ", ";
        if (errors.size() != 0)
            res += errors[errors.size()-1].key + ": " + errors[errors.size()-1].value;
        res += "}";
        return res.c_str();
    }
};


#endif //PSS_INCORRECTDATAEXCEPTION_H
