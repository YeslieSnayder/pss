//
// Created by yesliesnayder on 16.04.2021.
//

#ifndef PSS_ADMINSERVICE_H
#define PSS_ADMINSERVICE_H

#define ALLOWED 1   // The method is allowed
#define NOT_ALLOWED 0   // The method is not allowed

#include "../../include/rapidcsv/rapidcsv.h"
#include "objects/Passenger.h"
#include "objects/Driver.h"
#include "exceptions/NotFoundException.h"

using namespace std;


/**
 * File paths for Admin functionality.
 */
static const string CAR_VALIDATION_FILE = "application/db/db_admin_files/cars_validation.csv";
static const string DRIVER_VALIDATION_FILE = "application/db/db_admin_files/driver_validation.csv";
static const string PASSENGER_VALIDATION_FILE = "application/db/db_admin_files/passenger_validation.csv";


/**
 * The position of Passenger functions in the CSV-file.
 */
enum class PassengerFunction : int {
    LOGIN = 0, GET, PATCH, ASSIGN_RIDE, ORDER_RIDE, GET_CAR, GET_ORDER, GET_ORDER_HISTORY
};

/**
 * The position of Driver functions in the CSV-file.
 */
enum class DriverFunction: int {
    LOGIN = 0, GET, PATCH, GET_CAR, CHECK_ORDERS, ACCEPT_ORDER, COMPLETE_ORDER, GET_ORDER_HISTORY
};


/**
 * The class for admin to change ability of users do something.
 */
class AdminService {
public:

    /**
     * Allows all functions for passenger with id from input.
     * @param passenger_id - id of the passenger that can use any passenger's function.
     */
    static void allow_passenger_all(unsigned long int passenger_id) {
        rapidcsv::Document doc(PASSENGER_VALIDATION_FILE, rapidcsv::LabelParams(0, 0));

        doc.InsertRow<int>(passenger_id, {}, to_string(passenger_id));
        doc.SetCell<int>((int) PassengerFunction::LOGIN, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::GET, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::PATCH, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::ASSIGN_RIDE, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::ORDER_RIDE, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::GET_CAR, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::GET_ORDER, passenger_id, ALLOWED);
        doc.SetCell<int>((int) PassengerFunction::GET_ORDER_HISTORY, passenger_id, ALLOWED);
        doc.Save();
    }

    /**
     * Allows all functions for driver with id from input.
     * @param driver_id - id of the driver that can use any passenger's function.
     */
    static void allow_driver_all(unsigned long int driver_id) {
        rapidcsv::Document doc(DRIVER_VALIDATION_FILE, rapidcsv::LabelParams(0, 0));

        doc.InsertRow<int>(driver_id, {}, to_string(driver_id));
        doc.SetCell<int>((int) DriverFunction::LOGIN, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::GET, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::PATCH, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::GET_CAR, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::CHECK_ORDERS, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::ACCEPT_ORDER, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::COMPLETE_ORDER, driver_id, ALLOWED);
        doc.SetCell<int>((int) DriverFunction::GET_ORDER_HISTORY, driver_id, ALLOWED);
        doc.Save();
    }

    /**
     * Change the ability of the driver to do some function from input.
     * @param driver_id - identifier of the driver.
     * @param function - the function, the ability of which will be changed.
     * @param is_allowed - True => the function will be allowed for the driver,
     *  False => the function will not be allowed for the driver.
     */
    static void set_driver_ability(unsigned long int driver_id, DriverFunction function, bool is_allowed) {
        rapidcsv::Document doc(DRIVER_VALIDATION_FILE, rapidcsv::LabelParams(0, 0));
        if (driver_id <= 0 || driver_id >= doc.GetRowCount())
            throw NotFoundException(driver_id);
        if (is_allowed)
            doc.SetCell<int>((int) function, driver_id, ALLOWED);
        else
            doc.SetCell<int>((int) function, driver_id, NOT_ALLOWED);
        doc.Save();
    }

    /**
     * Change the ability of the passenger to do some function from input.
     * @param passenger_id - identifier of the passenger.
     * @param function - the function, the ability of which will be changed.
     * @param is_allowed - True => the function will be allowed for the passenger,
     *  False => the function will not be allowed for the passenger.
     */
    static void set_passenger_ability(unsigned long int passenger_id, PassengerFunction function, bool is_allowed) {
        rapidcsv::Document doc(PASSENGER_VALIDATION_FILE, rapidcsv::LabelParams(0, 0));
        if (passenger_id <= 0 || passenger_id >= doc.GetRowCount())
            throw NotFoundException(passenger_id);
        if (is_allowed)
            doc.SetCell<int>((int) function, passenger_id, ALLOWED);
        else
            doc.SetCell<int>((int) function, passenger_id, NOT_ALLOWED);
        doc.Save();
    }

    /**
     * Returns the ability of the driver to call the function from input.
     * @param driver_id - identifier of the driver.
     * @param function - the function, the ability of which will be checked.
     * @return True => if the function is allowed for the driver,
     *  False => if the function is not allowed for the driver.
     */
    static bool is_driver_function_allowed(unsigned long int driver_id, DriverFunction function) {
        rapidcsv::Document doc(DRIVER_VALIDATION_FILE, rapidcsv::LabelParams(0, 0));
        if (driver_id <= 0 || driver_id >= doc.GetRowCount())
            throw NotFoundException(driver_id);
        int res = doc.GetCell<int>((int) function, driver_id);
        if (res == ALLOWED)
            return true;
        return false;
    }

    /**
     * Returns the ability of the passenger to call the function from input.
     * @param passenger_id - identifier of the passenger.
     * @param function - the function, the ability of which will be checked.
     * @return True => if the function is allowed for the passenger,
     *  False => if the function is not allowed for the passenger.
     */
    static bool is_passenger_function_allowed(unsigned long int passenger_id, PassengerFunction function) {
        rapidcsv::Document doc(PASSENGER_VALIDATION_FILE, rapidcsv::LabelParams(0, 0));
        if (passenger_id <= 0 || passenger_id >= doc.GetRowCount())
            throw NotFoundException(passenger_id);
        int res = doc.GetCell<int>((int) function, passenger_id);
        if (res == ALLOWED)
            return true;
        return false;
    }
};

#endif //PSS_ADMINSERVICE_H
