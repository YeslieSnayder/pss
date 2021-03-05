//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_CABINET_H
#define PSS_CABINET_H

#include "Room.h"
#include "../Laboratory.h"
#include "../user/User.h"
#include "../user/LabEmployee.h"

class Cabinet : public Room {
    User owner;
    Laboratory lab;

public:
    static const AccessLevel ACCESS_LEVEL = GREEN;

    Cabinet(int number, User& owner) : Room(ACCESS_LEVEL, CABINET, number), owner(owner) {
        if (owner.getAccessLevel() == LabEmployee::ACCESS_LEVEL)
            lab = dynamic_cast<LabEmployee*>(&owner)->getLaboratory();
    }

    Cabinet(int number, Laboratory laboratory, User& owner) : Room(ACCESS_LEVEL, CABINET, number),
        lab(laboratory), owner(owner) {}

    Cabinet(int number, Laboratory laboratory) : Room(ACCESS_LEVEL, CABINET, number),
        lab(laboratory), owner(NULL_USER) {}

    const User &getOwner() const {
        return owner;
    }

    void setOwner(const User &owner) {
        this->owner = owner;
    }

    Laboratory getLaboratory() const {
        return lab;
    }

    void setLaboratory(Laboratory lab) {
        Cabinet::lab = lab;
    }
};


#endif //PSS_CABINET_H
