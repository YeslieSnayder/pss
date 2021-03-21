//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_LABORATORY_H
#define PSS_LABORATORY_H

enum Laboratory {
    NO_LABORATORY, // special value
    PSS,
    AGLA,
    TCS,
};

namespace Laboratory_nms {

    string toString(Laboratory lab) {
        switch (lab) {
            case PSS:
                return "PSS";
            case AGLA:
                return "AGLA";
            case TCS:
                return "TCS";

            default:
                return "Nothing";
        }
    }

    Laboratory toEnum(string lab) {
        if (lab == toString(PSS))
            return PSS;
        if (lab == toString(AGLA))
            return AGLA;
        if (lab == toString(TCS))
            return TCS;
        return NO_LABORATORY;
    }
}

#endif //PSS_LABORATORY_H
