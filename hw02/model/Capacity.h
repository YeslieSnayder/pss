//
// Created by Andrey Kuzmickiy group BS20-03.
//

#ifndef PSS_CAPACITY_H
#define PSS_CAPACITY_H

enum Capacity {
    CLASS_ROOM = 25,        // <= 25 people,  access = NO_LEVEL
    LECTURE_ROOM = 200,     // <= 200 people, access = NO_LEVEL
    CONFERENCE_ROOM = 50,   // <= 50 people, access = YELLOW
    CABINET = 5,            // <= 5 people,   access = RED
    DIRECTOR_CABINET = 1    // <= 1 person,   access = RED
};

namespace Capacity_nms {

    std::string toString(Capacity capacity) {
        switch (capacity) {
            case CLASS_ROOM: return "Class room";
            case LECTURE_ROOM: return "Lecture room";
            case CONFERENCE_ROOM: return "Conference room";
            case CABINET: return "Cabinet";
            case DIRECTOR_CABINET: return "Director cabinet";

            default: return "No such capacity";
        }
    }

    Capacity toEnum(std::string capacity) {
        if (capacity == "Class room")
            return CLASS_ROOM;
        if (capacity == "Lecture room")
            return LECTURE_ROOM;
        if (capacity == "Conference room")
            return CONFERENCE_ROOM;
        if (capacity == "Cabinet")
            return CABINET;
        if (capacity == "Director cabinet")
            return DIRECTOR_CABINET;
        return CLASS_ROOM;
    }
}

#endif //PSS_CAPACITY_H
