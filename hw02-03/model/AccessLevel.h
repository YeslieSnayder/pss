//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_ACCESSLEVEL_H
#define PSS_ACCESSLEVEL_H

#include <string>

enum AccessLevel {
    BLUE,
    NO_LEVEL,
    GREEN,
    YELLOW,
    RED,
    SUPER_USER
};

namespace AccessLevel_nms {

    std::string toString(AccessLevel level) {
        switch (level) {
            case NO_LEVEL:
                return "No level";
            case BLUE:
                return "Blue";
            case GREEN:
                return "Green";
            case YELLOW:
                return "Yellow";
            case RED:
                return "Red";
            case SUPER_USER:
                return "Admin";

            default: return "Non_type";
        }
    }

    AccessLevel toEnum(std::string level) {
        if (level == toString(BLUE))
            return BLUE;
        if (level == toString(GREEN))
            return GREEN;
        if (level == toString(YELLOW))
            return YELLOW;
        if (level == toString(RED))
            return RED;
        if (level == toString(SUPER_USER))
            return SUPER_USER;
        return NO_LEVEL;
    }

}

#endif //PSS_ACCESSLEVEL_H
