//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "../model/user/Student.h"
#include "../model/user/LabEmployee.h"
#include "../model/user/Professor.h"
#include "../model/user/Director.h"
#include "../model/user/Admin.h"

/**
 * The test is about the creation of all types of users and checks information about them.
 * @return 0 - if test is success,
 *  #number except zero (0) - if test with data (#number) is failed
 */
int main() {
    User *user;
    bool result;

    // Test values
    string name = "Ivan", surname = "Ivanov", extraInfo = "smt";
    uint age = 20, course = 4, workExperience = 10;
    AccessLevel level = NO_LEVEL;
    Laboratory lab = PSS;
    bool isPhd = false;

    // Test #1
    user = new User(name, surname, age, level, extraInfo);
    result = (name + " " + surname) == user->getName()
            && age == user->getAge()
            && level == user->getAccessLevel()
            && extraInfo == user->getExtraInfo();
    if (!result) return 1;

    // Test #2
    user = new Student(name, surname, age, course, extraInfo);
    result = (name + " " + surname) == user->getName()
            && age == user->getAge()
            && Student::ACCESS_LEVEL == user->getAccessLevel()
            && extraInfo == user->getExtraInfo()
            && course == ((Student *) user)->getCourse();
    if (!result) return 2;

    // Test #3
    user = new LabEmployee(name, surname, age, lab, isPhd, extraInfo);
    result = (name + " " + surname) == user->getName()
            && age == user->getAge()
            && LabEmployee::ACCESS_LEVEL == user->getAccessLevel()
            && extraInfo == user->getExtraInfo()
            && lab == ((LabEmployee *) user)->getLaboratory()
            && isPhd == ((LabEmployee *) user)->isPhd();
    if (!result) return 3;

    // Test #4
    user = new Professor(name, surname, age, lab, workExperience, extraInfo);
    result = (name + " " + surname) == user->getName()
             && age == user->getAge()
             && Professor::ACCESS_LEVEL == user->getAccessLevel()
             && extraInfo == user->getExtraInfo()
             && lab == ((Professor *) user)->getLaboratory()
             && workExperience == ((Professor *) user)->getWorkExperience();
    if (!result) return 4;

    // Test #5
    user = new Director(name, surname, age, extraInfo);
    result = (name + " " + surname) == user->getName()
             && age == user->getAge()
             && Director::ACCESS_LEVEL == user->getAccessLevel()
             && extraInfo == user->getExtraInfo();
    if (!result) return 5;

    // Test #6
    user = new Admin(name, surname, age, extraInfo);
    result = (name + " " + surname) == user->getName()
             && age == user->getAge()
             && Admin::ACCESS_LEVEL == user->getAccessLevel()
             && extraInfo == user->getExtraInfo();
    if (!result) return 6;
}