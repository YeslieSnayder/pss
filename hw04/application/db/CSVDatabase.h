//
// Created by yesliesnayder on 15.04.2021.
//

#ifndef PSS_CSVDATABASE_H
#define PSS_CSVDATABASE_H

#include "../../include/rapidcsv/rapidcsv.h"
#include "database.h"

class CSVDatabase : public Database {

    /**
     * Database file paths.
     */
    const string CAR_DB_FILEPATH = "application/db/db_files/cars.csv";
    const string ORDER_DB_FILEPATH = "application/db/db_files/orders.csv";
    const string DRIVER_DB_FILEPATH = "application/db/db_files/drivers.csv";
    const string PASSENGER_DB_FILEPATH = "application/db/db_files/passengers.csv";

public:

    //////////////   DRIVERS   //////////////

    virtual unsigned long int createDriver(Driver& driver) {
        rapidcsv::Document driver_doc(DRIVER_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));

        driver.setId(driver_doc.GetRowCount() + 1);
        vector<Car> cars = driver.getPersonalCars();
        for (auto & car : cars)
            car.setDriverId(driver.getId());

        // Driver data
        unsigned long int id = driver.getId() - 1;
        string name = driver.getName();
        double rating = driver.getRating();
        string status;
        if (driver.getStatus() == DriverStatus::NOT_WORKING)
            status = "not_working";
        else if (driver.getStatus() == DriverStatus::WORKING)
            status = "working";
        else if (driver.getStatus() == DriverStatus::IN_RIDE)
            status = "in_ride";
        else
            status = "not_working";

        driver_doc.InsertRow<int>(id, {}, to_string(driver.getId()));
        driver_doc.SetCell<string>(0, id, name);
        driver_doc.SetCell<double>(1, id, rating);
        driver_doc.SetCell<string>(2, id, status);
        driver_doc.Save();

        for (auto & car : cars)
            createCar(car);
    }

    virtual void createCar(Car& car) {
        rapidcsv::Document car_doc(CAR_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));

        // Car data
        string number = car.getNumber();   // identifier
        string model = car.getModel();
        string color = car.getColor();
        // + driver_id = id
        unsigned int freeBottleOfWater = car.getFreeBottleOfWater();
        string carType;
        if (car.getCarType() == CarType::Economy)
            carType = "economy";
        else if (car.getCarType() == CarType::Comfort)
            carType = "comfort";
        else if (car.getCarType() == CarType::ComfortPlus)
            carType = "comfort_plus";
        else if (car.getCarType() == CarType::Business)
            carType = "business";

        long int car_id = car_doc.GetRowCount();
        car_doc.InsertRow<int>(car_id, {}, to_string(car_id + 1));
        car_doc.SetCell<string>(0, car_id, number);
        car_doc.SetCell<string>(1, car_id, model);
        car_doc.SetCell<string>(2, car_id, color);
        car_doc.SetCell<string>(3, car_id, carType);
        car_doc.SetCell<int>(4, car_id, freeBottleOfWater);
        car_doc.SetCell<int>(5, car_id, car.getDriverId());
        car_doc.Save();
    }

    virtual Driver* getDriver(Driver& driver) {
        rapidcsv::Document doc(DRIVER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

        for (unsigned long int i = 0; i < doc.GetRowCount(); i++) {
            vector<string> obj = doc.GetRow<string>(i);

            string name = obj[0];
            double rating = stod(obj[1]);
            string status_str = obj[2];
            DriverStatus status;
            if (status_str == "not_working" || status_str == "not working")
                status = DriverStatus::NOT_WORKING;
            else if (status_str == "in_ride" || status_str == "in ride")
                status = DriverStatus::IN_RIDE;
            else if (status_str == "working")
                status = DriverStatus::WORKING;

            if (name == driver.getName() && rating == driver.getRating() && status == driver.getStatus()) {
                vector<Car> cars = getCars(i+1);
                return new Driver(i+1, name, rating, cars, status);
            }
        }
        return nullptr;
    }

    virtual Driver* getDriver(unsigned long int driver_id) {
        rapidcsv::Document doc(DRIVER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        if (driver_id > doc.GetRowCount())
            return nullptr;
        vector<string> obj = doc.GetRow<string>(driver_id - 1);

        string name = obj[0];
        double rating = stod(obj[1]);
        string status_str = obj[2];
        DriverStatus status;
        if (status_str == "not_working" || status_str == "not working")
            status = DriverStatus::NOT_WORKING;
        else if (status_str == "in_ride" || status_str == "in ride")
            status = DriverStatus::IN_RIDE;
        else if (status_str == "working")
            status = DriverStatus::WORKING;
        vector<Car> cars = getCars(driver_id);
        return new Driver(driver_id, name, rating, cars, status);
    }

    virtual Driver* patchDriver(Driver& driver) {
        rapidcsv::Document driver_doc(DRIVER_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));
        if (driver.getId() > driver_doc.GetRowCount())
            return nullptr;

        unsigned long int id = driver.getId() - 1;
        string name = driver.getName();
        double rating = driver.getRating();
        string status;
        if (driver.getStatus() == DriverStatus::NOT_WORKING)
            status = "not_working";
        else if (driver.getStatus() == DriverStatus::WORKING)
            status = "working";
        else if (driver.getStatus() == DriverStatus::IN_RIDE)
            status = "in_ride";
        else
            status = "not_working";

        driver_doc.SetCell<string>(0, id, name);
        driver_doc.SetCell<double>(1, id, rating);
        driver_doc.SetCell<string>(2, id, status);
        driver_doc.Save();
        return &driver;
    }

    /////////////   PASSENGERS   /////////////

    virtual unsigned long int createPassenger(Passenger& passenger) {
        rapidcsv::Document doc(PASSENGER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

        passenger.setId(doc.GetRowCount() + 1);

        // Passenger data
        unsigned long int id = passenger.getId() - 1;
        string name = passenger.getName();
        double rating = passenger.getRating();
        string payment;
        if (passenger.getPaymentMethod() == PaymentMethod::CASH)
            payment = "cash";
        else if (passenger.getPaymentMethod() == PaymentMethod::ONLINE)
            payment = "online";
        else if (passenger.getPaymentMethod() == PaymentMethod::BANK_BILL)
            payment = "bank_bill";
        else
            payment = "cash";

        doc.InsertRow<int>(id, {}, to_string(passenger.getId()));
        doc.SetCell<string>(0, id, name);
        doc.SetCell<double>(1, id, rating);
        doc.SetCell<string>(2, id, payment);
        doc.Save();

        return passenger.getId();
    }

    virtual Passenger* getPassenger(Passenger& passenger) {
        rapidcsv::Document doc(PASSENGER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

        for (unsigned long int i = 0; i < doc.GetRowCount(); i++) {
            vector<string> obj = doc.GetRow<string>(i);

            string name = obj[0];
            double rating = stod(obj[1]);
            string payment_str = obj[2];
            PaymentMethod payment;
            if (payment_str == "cash")
                payment = PaymentMethod::CASH;
            else if (payment_str == "online")
                payment = PaymentMethod::ONLINE;
            else if (payment_str == "bank_bill" || payment_str == "bank bill")
                payment = PaymentMethod::BANK_BILL;

            if (name == passenger.getName() && rating == passenger.getRating() && payment == passenger.getPaymentMethod()) {
                return new Passenger(i+1, name, rating, payment);
            }
        }
        return nullptr;
    }

    virtual Passenger* getPassenger(unsigned long int passenger_id) {
        rapidcsv::Document doc(PASSENGER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        if (passenger_id > doc.GetRowCount())
            return nullptr;
        vector<string> obj = doc.GetRow<string>(passenger_id - 1);

        string name = obj[0];
        double rating = stod(obj[1]);
        string payment_str = obj[2];
        PaymentMethod payment;
        if (payment_str == "cash")
            payment = PaymentMethod::CASH;
        else if (payment_str == "online")
            payment = PaymentMethod::ONLINE;
        else if (payment_str == "bank_bill" || payment_str == "bank bill")
            payment = PaymentMethod::BANK_BILL;
        return new Passenger(passenger_id, name, rating, payment);
    }

    virtual Passenger* patchPassenger(Passenger& passenger) {
        rapidcsv::Document doc(PASSENGER_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));
        if (passenger.getId() > doc.GetRowCount())
            return nullptr;

        unsigned long int id = passenger.getId() - 1;
        string name = passenger.getName();
        double rating = passenger.getRating();
        string payment;
        if (passenger.getPaymentMethod() == PaymentMethod::CASH)
            payment = "cash";
        else if (passenger.getPaymentMethod() == PaymentMethod::ONLINE)
            payment = "online";
        else if (passenger.getPaymentMethod() == PaymentMethod::BANK_BILL)
            payment = "bank_bill";
        else
            payment = "online";

        doc.SetCell<string>(0, id, name);
        doc.SetCell<double>(1, id, rating);
        doc.SetCell<string>(2, id, payment);
        doc.Save();
        return &passenger;
    }

    /////////////   CARS   /////////////

    virtual vector<Car> getCars(unsigned long int driver_id) {
        rapidcsv::Document car_doc(CAR_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));

        vector<Car> cars;
        for (unsigned long int i = 0; i < car_doc.GetRowCount(); i++) {
            int d_id = stoi(car_doc.GetCell<string>(5, i));
            if (d_id == driver_id) {
                vector<string> obj = car_doc.GetRow<string>(i);

                string number = obj[0];
                string model = obj[1];
                string color = obj[2];
                int freeBottleOfWater = stoi(obj[4]);
                CarType carType;
                string carType_str = obj[3];
                if (carType_str == "economy")
                    carType = CarType::Economy;
                else if (carType_str == "comfort")
                    carType = CarType::Comfort;
                else if (carType_str == "comfort_plus")
                    carType = CarType::ComfortPlus;
                else if (carType_str == "business")
                    carType = CarType::Business;

                Car car(number, model, color, carType, freeBottleOfWater, driver_id);
                cars.push_back(car);
            }
        }
        return cars;
    }

    virtual Car* getCar(string number) {
        rapidcsv::Document car_doc(CAR_DB_FILEPATH, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(',', false, false));

        for (unsigned long int i = 0; i < car_doc.GetRowCount(); i++) {
            string number_str = car_doc.GetCell<string>(0, i);
            if (number_str == number) {
                vector<string> obj = car_doc.GetRow<string>(i);

                string model = obj[1];
                string color = obj[2];
                int freeBottleOfWater = stoi(obj[4]);
                int driver_id = stoi(obj[5]);
                CarType carType;
                string carType_str = obj[3];
                if (carType_str == "economy")
                    carType = CarType::Economy;
                else if (carType_str == "comfort")
                    carType = CarType::Comfort;
                else if (carType_str == "comfort_plus")
                    carType = CarType::ComfortPlus;
                else if (carType_str == "business")
                    carType = CarType::Business;

                return new Car(number, model, color, carType, freeBottleOfWater, driver_id);
            }
        }
        return nullptr;
    }

    /////////////   ORDERS   /////////////

    virtual Order* createOrder(Order& order) {
        rapidcsv::Document doc(ORDER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));

        order.setId(doc.GetRowCount() + 1);

        // Order data
        unsigned long int id = order.getId() - 1;
        GEOAddress startPoint = order.getStartPoint();
        GEOAddress destination= order.getDestination();
        string startTime = order.getStartTime();
        double price = order.getPrice();
        unsigned long int passenger_id = order.getPassengerId();
        unsigned long int driver_id = order.getDriverId();
        string status;
        if (order.getStatus() == OrderStatus::READY)
            status = "ready";
        else if (order.getStatus() == OrderStatus::PROCESSING)
            status = "processing";
        else if (order.getStatus() == OrderStatus::COMPLETE)
            status = "complete";
        else
            status = "ready";

        doc.InsertRow<int>(id, {}, to_string(order.getId()));
        doc.SetCell<string>(0, id, startPoint.geoString());
        doc.SetCell<string>(1, id, destination.geoString());
        doc.SetCell<string>(2, id, startTime);
        doc.SetCell<double>(3, id, price);
        doc.SetCell<long int>(4, id, passenger_id);
        doc.SetCell<long int>(5, id, driver_id);
        doc.SetCell<string>(6, id, status);
        doc.Save();

        return &order;
    }

    virtual Order* changeOrder(Order& order) {
        rapidcsv::Document doc(ORDER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        if (order.getId() > doc.GetRowCount())
            return nullptr;

        unsigned long int id = order.getId() - 1;
        GEOAddress startPoint = order.getStartPoint();
        GEOAddress destination= order.getDestination();
        string startTime = order.getStartTime();
        double price = order.getPrice();
        unsigned long int passenger_id = order.getPassengerId();
        unsigned long int driver_id = order.getDriverId();
        string status;
        if (order.getStatus() == OrderStatus::READY)
            status = "ready";
        else if (order.getStatus() == OrderStatus::PROCESSING)
            status = "processing";
        else if (order.getStatus() == OrderStatus::COMPLETE)
            status = "complete";
        else
            status = "ready";

        doc.SetCell<string>(0, id, startPoint.geoString());
        doc.SetCell<string>(1, id, destination.geoString());
        doc.SetCell<string>(2, id, startTime);
        doc.SetCell<double>(3, id, price);
        doc.SetCell<long int>(4, id, passenger_id);
        doc.SetCell<long int>(5, id, driver_id);
        doc.SetCell<string>(6, id, status);
        doc.Save();
    }

    virtual Order* getOrder(unsigned long int order_id) {
        rapidcsv::Document doc(ORDER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        if (order_id > doc.GetRowCount())
            return nullptr;
        vector<string> obj = doc.GetRow<string>(order_id - 1);

        GEOAddress startPoint(obj[0]);
        GEOAddress destination(obj[1]);
        string startTime = obj[2];
        double price = stod(obj[3]);
        unsigned long int passenger_id = doc.GetCell<int>(4, order_id - 1);
        unsigned long int driver_id = doc.GetCell<int>(5, order_id - 1);
        string status_str = doc.GetCell<string>(6, order_id - 1);
        OrderStatus status;
        if (status_str == "ready")
            status = OrderStatus::READY;
        else if (status_str == "processing")
            status = OrderStatus::PROCESSING;
        else if (status_str == "complete")
            status = OrderStatus::COMPLETE;
        else
            status = OrderStatus::READY;

        return new Order(order_id, startPoint, destination, startTime, price, passenger_id, driver_id, status);
    }

    virtual Order* getLastOrder(unsigned long int id, ObjectType type) {
        vector<Order> prevOrders = getOrderHistory(id, type);
        if (prevOrders.empty())
            return nullptr;
        int max_id = 0, index;
        for (int i = 0; i < prevOrders.size(); i++) {
            if (prevOrders[i].getId() > max_id) {
                max_id = prevOrders[i].getId();
                index = i;
            }
        }
        return &prevOrders[index];
    }

    virtual vector<Order> getOrderHistory(unsigned long int id, ObjectType type) {
        rapidcsv::Document doc(ORDER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        vector<Order> orders;

        for (unsigned long int i = 0; i < doc.GetRowCount(); i++) {
            unsigned long int passenger_id = doc.GetCell<int>(4, i);
            unsigned long int driver_id = doc.GetCell<int>(5, i);
            if (passenger_id == id && type == ObjectType::PASSENGER ||
                   driver_id == id && type == ObjectType::DRIVER) {
                vector<string> obj = doc.GetRow<string>(i);

                unsigned long int id = i + 1;
                GEOAddress startPoint(obj[0]);
                GEOAddress destination(obj[1]);
                string startTime = obj[2];
                float price = stod(obj[3]);
                string status_str = doc.GetCell<string>(6, i);
                OrderStatus status;
                if (status_str == "ready")
                    status = OrderStatus::READY;
                else if (status_str == "processing")
                    status = OrderStatus::PROCESSING;
                else if (status_str == "complete")
                    status = OrderStatus::COMPLETE;
                else
                    status = OrderStatus::READY;

                Order order(id, startPoint, destination, startTime, price, passenger_id, driver_id, status);
                orders.push_back(order);
            }
        }
        return orders;
    }

    virtual vector<Order> getAvailableOrders() {
        rapidcsv::Document doc(ORDER_DB_FILEPATH, rapidcsv::LabelParams(0, 0));
        vector<Order> orders;

        for (unsigned long int i = 0; i < doc.GetRowCount(); i++) {
            string status_str = doc.GetCell<string>(6, i);
            if (status_str == "ready") {
                vector<string> obj = doc.GetRow<string>(i);

                unsigned long int id = i + 1; // -1
                GEOAddress startPoint(obj[0]);
                GEOAddress destination(obj[1]);
                string startTime = obj[2];
                float price = stod(obj[3]);
                unsigned long int passenger_id = stoi(obj[4]);
                unsigned long int driver_id = stoi(obj[5]);
                OrderStatus status = OrderStatus::READY;

                Order order(id, startPoint, destination, startTime, price, passenger_id, driver_id, status);
                orders.push_back(order);
            }
        }
        return orders;
    }
};


#endif //PSS_CSVDATABASE_H
