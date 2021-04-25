//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_ADDRESS_H
#define PSS_ADDRESS_H

#include <math.h>
#include "../exceptions/IncorrectDataException.h"

/**
 * The class represents the address of a car, pinned addresses of a passenger, and the destination.
 * It has latitude and longitude in standard form of ISO 6709 (degree: deg.)
 * Example:
 *  New York: +40.75-74.00 where 40.75 is latitude, -74.00 is longitude.
 */
class GEOAddress {
    double latitude;    // -90.0 to 90.0
    double longitude;   // -180.0 to 180.0

public:
    GEOAddress(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

    GEOAddress(std::string& address_str) {
        if (!is_correct_address(address_str)) {
            IncorrectDataException::Entry error;
            error.key = "address";
            error.value = "GEOAddress: Parameter 'address' is incorrect, expected example: '+40.75-74.00'"
                          ", but given: " + address_str;
            throw IncorrectDataException({error});
        }

        bool neg = address_str[0] == '-';
        std::string num;
        for (int i = 1; i < address_str.size(); i++) {
            if (address_str[i] == '+' || address_str[i] == '-') {
                latitude = std::stod(num);
                if (neg) latitude = -latitude;
                num.clear();
                if (address_str[i] == '+') neg = false;
                else if (address_str[i] == '-') neg = true;
            } else
                num.push_back(address_str[i]);
        }
        longitude = std::stod(num);
        if (neg) longitude = -longitude;
    }

    /**
     * Returns geo position in standard form of ISO 6709 (in degrees).
     * @return string with coordinates.
     */
    std::string geoString() const {
        if (this == NULL) return "";
        return ((latitude < 0) ? '-' : '+') + std::to_string(latitude) +
                ((longitude < 0) ? '-' : '+') + std::to_string(longitude);
    }

    /**
     * Returns the distance between start and end points.
     * @param start - the object of GEOAddress class: start point.
     * @param end - the object of GEOAddress class: destination.
     * @return absolute value of distance between 2 points.
     */
    static double getDistance(GEOAddress start, GEOAddress end) {
        double lat = end.latitude - start.latitude;
        double lon = end.longitude - start.longitude;
        return sqrt(pow(lat, 2) + pow(lon, 2));
    }

    GEOAddress& operator=(GEOAddress other) {
        this->latitude = other.latitude;
        this->longitude = other.longitude;
        return *this;
    }

    bool operator==(const GEOAddress& obj) const {
        return latitude == obj.latitude && longitude == obj.longitude;
    }

    bool operator!=(const GEOAddress& obj) const {
        return !(operator==(obj));
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    void setLatitude(double latitude) {
        if (latitude < -90.0 || latitude > 90.0)
            throw std::range_error("Incorrect input latitude. Expected: -90.0 <= latitude <= 90.0, "
                    "but given " + std::to_string(latitude));
        GEOAddress::latitude = latitude;
    }

    void setLongitude(double longitude) {
        if (longitude < -180.0 || longitude > 180.0)
            throw std::range_error("Incorrect input longitude. Expected: -180.0 <= longitude <= 180.0, "
                                   "but given " + std::to_string(longitude));
        GEOAddress::longitude = longitude;
    }

    /**
     * Validates the string and returns the result.
     * @param val - string is represented an object of the address.
     * @return The result of validation:
     *  True => If address is correct;
     *  False => If address is incorrect.
     */
    static bool is_correct_address(std::string& val) {
        if (val[0] != '-' && val[0] != '+')
            return false;
        std::string s = val;
        int sign_count = 0, comma_count = 0;
        for (char& c : s) {
            if (c == '-' || c == '+')
                sign_count++;
            else if (c == ',' || c == '.')
                comma_count++;
            if (sign_count > 2 || comma_count > 2)
                return false;
            if ((c < '0' || c > '9') && c != '+' && c != '-' && c != '.' && c != ',')
                return false;
        }
        return true;
    }
};

#endif //PSS_ADDRESS_H
