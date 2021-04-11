//
// Created by yesliesnayder on 03.04.2021.
//

#ifndef PSS_ADDRESS_H
#define PSS_ADDRESS_H

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

    /**
     * Returns geo position in standard form of ISO 6709 (in degrees).
     * @return string with coordinates.
     */
    std::string geoString() const {
        return ((latitude < 0) ? '-' : '+') + std::to_string(latitude) +
                ((longitude < 0) ? '-' : '+') + std::to_string(longitude);
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

    GEOAddress(std::string address_str) {
        bool neg = address_str[0] == '-';
        std::string num;
        for (int i = 1; i < address_str.size(); i++) {
            if (address_str[i] == '+' || address_str[i] == '-') {
                latitude = std::stod(num);
                if (neg) latitude = -latitude;
                num.clear();
            } else
                num.push_back(address_str[i]);
        }
    }
};

#endif //PSS_ADDRESS_H
