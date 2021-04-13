//
// Created by yesliesnayder on 11.04.2021.
//

#include <utility>
#include <vector>

#ifndef PSS_INCORRECTDATAEXCEPTION_H
#define PSS_INCORRECTDATAEXCEPTION_H


class IncorrectDataException : public std::exception {
    struct Entry {
        std::string key;
        std::string value;
    };
    std::vector<Entry> errors{};

public:
    IncorrectDataException() {}
    IncorrectDataException(std::vector<Entry> errors) : errors(std::move(errors)) {}

    void addEntry(std::string key, std::string value) {
        errors.push_back({key, value});
    }

    const std::vector<Entry> &getErrors() const {
        return errors;
    }

    virtual bool hasErrors() const {
        return !errors.empty();
    }

    virtual std::string to_string(std::vector<Entry>& error_list) const {
        std::string res = "{";
        for (int i = 0; i < error_list.size() - 1; i++)
            res += error_list[i].key + ": " + error_list[i].value + ", ";
        if (error_list.size() != 0)
            res += error_list[error_list.size() - 1].key + ": " + error_list[error_list.size() - 1].value;
        res += "}";
        return res;
    }
};


#endif //PSS_INCORRECTDATAEXCEPTION_H
