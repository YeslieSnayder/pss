//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include <iostream>

#include "services/RoomService.cpp"
#include "services/CSVService.cpp"

using namespace std;

User* logIn(vector<User*> &users);
User* signUp();
void work(User *user, vector<User*> &users);
void printAllRooms(User* user, vector<Room*> &rooms);
Room* getRoom(int number, vector<Room*> &rooms);
void toLowerCase(string &str);
bool isRightRole(string &role);
int isRightName(vector<User*> &users, string &role, string &name);

int main() {
    string s;
    cout << "Do you want to sing up (1) or you have an account (2)? (1 or 2): ";
    User* user;
    vector<User*> users = getUsers();
    while (1) {
        getline(cin, s);
        if (s == "1") {
            user = signUp();
            if (user != nullptr)
                work(user, users);
            break;
        } else if (s == "2") {
            user = logIn(users);
            if (user != nullptr)
                work(user, users);
            break;
        }
        cout << "You should write only 1 or 2: ";
    }
}

/**
 * The main method for interactive work. It allows user to choose the action which it will do.
 * @param user - the person who logged in
 * @param users - the database of all people
 */
void work(User *user, vector<User*> &users) {
    bool isAdmin = user->getAccessLevel() == SUPER_USER;
    cout << "You have logged in account: " << user->getName() << endl;
    vector<Room*> rooms = getRooms(users);
    printAllRooms(user, rooms);
    string command;
    while (true) {
        cout << endl << "You can enter the room (1), "
             << "leave the room (2), "
             << "list all rooms (3), "
             << "print information about you (4), "
             << (isAdmin ? "print information about all user (5), give access for user to the room (6), " : "")
             << "exit the program (exit)" << endl;
        cin >> command;
        if (command == "1") {
            log("Enter the number of room: ");
            int num;
            cin >> num;
            Room *room = getRoom(num, rooms);
            if (room == nullptr) {
                log(WARNING, "No room with number " + num);
                command = "";
                continue;
            }
            try {
                enterRoom(user, room);
            } catch (WrongAccessException e) {
                log(ERROR, e.message());
            }
        } else if (command == "2") {
            log("Enter the number of room: ");
            int num;
            cin >> num;
            Room *room = getRoom(num, rooms);
            if (room == nullptr) {
                log(WARNING, "No room with number " + num);
                command = "";
                continue;
            }
            try {
                leaveRoom(user, room);
            } catch (WrongAccessException e) {
                log(ERROR, e.message());
            }
        } else if (command == "3") {
            printAllRooms(user, rooms);
        } else if (command == "4") {
            user->printInfo();
        } else if (command == "5" && isAdmin) {
            for (User *u : users) {
                u->printInfo();
            }
        } else if (command == "6" && isAdmin) {
            log("Please, write id of the USER:");
            int userId;
            cin >> userId;
            log("Please, write number of the ROOM:");
            int numRoom;
            cin >> numRoom;
            Admin *admin = dynamic_cast<Admin*>(user);
            admin->giveAccess(*user, *getRoom(numRoom, rooms));
        } else if (command == "exit") {
            break;
        } else
            log(WARNING, "Sorry, command is unreachable. Please, try again");
    }

    bool hasUser = false;
    for (User *u : users) {
        if (user->equals(u)) {
            hasUser = true;
            break;
        }
    }
    if (!hasUser) {
        users.push_back(user);
    }
}

/**
 * The method reads database and tries to find the person by parameters which user is writing in terminal.
 * @param users - database of people
 * @return Pointer to the person which has parameters which user has written in terminal.
 */
User* logIn(vector<User*> &users) {
    string role, name;
    cout << "Please, select one of the available roles (Student, Lab employee, Professor, Director, Admin): ";
    getline(cin, role);
    while (!isRightRole(role)) {
        cout << "Available roles are Student, Lab employee, Professor, Director, Admin: ";
        getline(cin, role);
        if (role == "exit") return nullptr;
    }
    cout << "Please, enter your full name: ";
    getline(cin, name);

    int userId = isRightName(users, role, name);
    while (userId == -1) {
        cout << "The name " << name << " with access level (" << role
             << ") doesn't exist in data base. Do you want to enter another name? (y/n) " << endl;
        getline(cin, name);
        if (name == "n") return nullptr;
        cout << "Enter your full name: ";
        getline(cin, name);
        userId = isRightName(users, role, name);
    }

    User* res = nullptr;
    for (auto & user : users) {
        if (user->getId() == userId) {
            res = user;
            break;
        }
    }

    if (role == "admin" && res != nullptr) {
        string pass;
        cout << "Please, enter the password: ";
        cin >> pass;

        Admin* admin = dynamic_cast<Admin*>(res);

        while (pass != admin->getPassword()) {
            cout << "Password was incorrect. Please, enter your password again ('exit' - to close the program)" << endl;
            cin >> pass;
            if (pass == "exit") return nullptr;
        }
        return admin;
    }
    return res;
}

/**
 * The method needs to sign up new user. Each type of user has his own details, all of them the user should fill up.
 * @return Pointer to the new user, which was created by this method.
 *  nullptr - if user wasn't created, program was terminated.
 */
User* signUp() {
    string s, role, name, extraInfo;
    int age;
    cout << "Please, select one of the available roles (Student, Lab employee, Professor, Director, Admin): ";
    getline(cin, s);
    while (!isRightRole(s)) {
        cout << "Available roles are Student, Lab employee, Professor, Director, Admin: ";
        cin >> s;
        if (s == "exit") return nullptr;
    }
    role = s;
    cout << "Please, enter your name: ";
    cin >> name;
    cout << "Please, enter your age (age > 16): ";
    cin >> age;
    while (age <= 16) {
        cout << "Please, enter your age (age > 16): ";
        cin >> age;
    }
    cout << "Do you want to provide some extra information about you? (y/n) ";
    cin >> s;
    if (s == "y") {
        cout << "Please, enter extra information: ";
        cin >> extraInfo;
    }

    if (role == "student") {
        log("Student has to have a course number. Please, write your course:");
        int course;
        cin >> s;
        while (s.size() != 1 || !(s[0] > '0' && s[0] < '6')) {
            log("The course is incorrect. Please, write your course number:");
            cin >> s;
        }
        course = s[0] - '0';
        if (extraInfo.empty())
            return createUser(role, name, "", age, NO_LEVEL, course,
                          NO_LABORATORY, 0, false);
        else
            return createUser(role, name, "", age, NO_LEVEL, course,
                              NO_LABORATORY, 0, false, extraInfo);
    } else if (role == "lab employee") {
        log("Lab employee has to have laboratory name.");
        log("Please, write your laboratory (AGLA, TCS, PSS):");
        string str;
        cin >> str;
        Laboratory lab = Laboratory_nms::toEnum(str);
        log("You have chosen: " + Laboratory_nms::toString(lab));
        log("Are you Phd student? (y/n)");
        cin >> str;
        bool phd = str == "y";
        if (extraInfo.empty())
            return createUser(role, name, "", age, GREEN, 0,
                              lab, 0, phd);
        else
            return createUser(role, name, "", age, GREEN, 0,
                              lab, 0, phd, extraInfo);
    } else if (role == "professor") {
        log("Professor has to have work experience and his subject (just one).");
        log("Please, write your laboratory (AGLA, TCS, PSS):");
        string str;
        cin >> str;
        Laboratory lab = Laboratory_nms::toEnum(str);
        log("You have chosen: " + Laboratory_nms::toString(lab));

        int workExperience = -1;
        while (workExperience < 0 || workExperience > age) {
            log("Please, write your work experience (in years):");
            cin >> workExperience;
        }
        if (extraInfo.empty())
            return createUser(role, name, "", age, YELLOW, 0,
                              lab, workExperience, false);
        else
            return createUser(role, name, "", age, YELLOW, 0,
                              lab, workExperience, false, extraInfo);
    } else if (role == "director") {
        if (extraInfo.empty())
            return createUser(role, name, "", age, RED, 0,
                              NO_LABORATORY, 0, false);
        else
            return createUser(role, name, "", age, RED, 0,
                              NO_LABORATORY, 0, false, extraInfo);
    } else if (role == "admin") {
        log("Each admin has to have their own password.");
        log("Please, write your password:");
        string password;
        getline(cin, password);
        getline(cin, password);
        if (extraInfo.empty())
            return createUser(role, name, "", age, SUPER_USER, 0,
                              NO_LABORATORY, 0, false, password=password);
        else
            return createUser(role, name, "", age, SUPER_USER, 0,
                              NO_LABORATORY, 0, false, extraInfo=extraInfo, password=password);
    }
    cout << "Sorry, but we cannot create type of user: " << role;
    return nullptr;
}

/**
 * Checks name of person (@param name) by his type (role). Returns the id of person in database.
 * @param users - database of people
 * @param role - the type of user (Student, Professor, Admin, etc.)
 * @param name - the name which should be checked
 * @return id of person who has the type (@param role) and name (@param name)
 */
int isRightName(vector<User*> &users, string &role, string &name) {
    toLowerCase(role);
    toLowerCase(name);
    for (User* user : users) {
        string userName = user->getName();
        toLowerCase(userName);
        if (userName == name) {
            AccessLevel level = user->getAccessLevel();
            switch (level) {
                case NO_LEVEL:
                    if (role == "student") return user->getId();
                    break;
                case GREEN:
                    if (role == "lab employee") return user->getId();
                    break;
                case YELLOW:
                    if (role == "professor") return user->getId();
                    break;
                case RED:
                    if (role == "director") return user->getId();
                    break;
                case SUPER_USER:
                    if (role == "admin") return user->getId();
                    break;
            }
        }
    }
    return -1;
}

/**
 * Checks the type of person. All types of person are listed in the directory (model/user)
 * @param role - the type of person which will be checked
 * @return true - if the type is correct
 *  false - otherwise
 */
bool isRightRole(string &role) {
    toLowerCase(role);
    return role == "student" || role == "lab employee" || role == "professor" || role == "director" || role == "admin";
}

/**
 * Prints all necessary information about rooms, including access of room by user.
 * @param user
 * @param rooms
 */
void printAllRooms(User* user, vector<Room*> &rooms) {
    log("List of all rooms:");
    for (auto &room : rooms) {
        bool isAvailable = room->isAcceptableUserForThisRoom(*user);
        if (!isAvailable && user->getAccessLevel() == LabEmployee::ACCESS_LEVEL
                         && room->getAccessLevel() == Cabinet::ACCESS_LEVEL) {
            LabEmployee *labEmployee = dynamic_cast<LabEmployee*>(user);
            Cabinet *cabinet = dynamic_cast<Cabinet*>(room);
            isAvailable = labEmployee->getLaboratory() == cabinet->getLaboratory();
        }
        cout << "Room number: " << room->getNumber()
             << ", type of room: " << Capacity_nms::toString(room->getCapacity())
             << ", is available: " << (isAvailable ? "YES" : "NO access") << endl;
    }
}

/**
 * Returns the room by his number
 * @return the room by his number
 */
Room* getRoom(int number, vector<Room*> &rooms) {
    for (Room *room : rooms) {
        if (number == room->getNumber())
            return room;
    }
    return nullptr;
}