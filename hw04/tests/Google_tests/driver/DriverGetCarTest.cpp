//
// Created by yesliesnayder on 14.04.2021.
//

#include "gtest/gtest.h"

#include <iostream>
#include <fstream>

#include "../../../application/db/TestDatabase.h"
#include "../../../application/model/model.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace rapidjson;
using namespace std;

class DriverGetCarTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    DriverGetCarTest() {
        ifstream ifs{R"(tests/Google_tests/data/driver_data.json)"};
        if ( !ifs.is_open() )
        {
            std::cerr << "Could not open file for reading!\n";
            throw exception();
        }

        IStreamWrapper isw{ifs};
        json.ParseStream(isw);

        StringBuffer buffer{};
        Writer<StringBuffer> writer{buffer};
        json.Accept(writer);

        if ( json.HasParseError() )
        {
            std::cout << "Error  : " << json.GetParseError()  << '\n'
                      << "Offset : " << json.GetErrorOffset() << '\n';
            throw exception();
        }
    }

    virtual void SetUp() {
        db = new TestDatabase();
        model = new Model(db);

        Document driver;
        driver.CopyFrom(json["correct"][0]["driver_1"], json.GetAllocator());
        model->createDriver(driver);
        driver.CopyFrom(json["correct"][1]["driver_2"], json.GetAllocator());
        model->createDriver(driver);
        driver.CopyFrom(json["correct"][2]["driver_3"], json.GetAllocator());
        model->createDriver(driver);
        driver.CopyFrom(json["correct"][3]["driver_4"], json.GetAllocator());
        model->createDriver(driver);
    }

    virtual void TearDown() {
        delete model;
        delete db;
    }
};

TEST_F(DriverGetCarTest, ExampleData_1) {
    Driver driver = *model->getDriver(1);
    Car car = driver.getPersonalCars()[0];

    Car test_car = car;
    try {
        Driver* test_driver = model->getDriver(1);
        test_car = (test_driver->getPersonalCars()[0]);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(car.getDriverId(), driver.getId());
    EXPECT_EQ(car.getModel(), "Lada Sedan");
    EXPECT_EQ(car.getNumber(), "A200BC");
    EXPECT_EQ(car.getColor(), "black");
    EXPECT_TRUE(car.getCarType() == CarType::Economy);

    // Check data from database
    EXPECT_EQ(car.getDriverId(), test_car.getDriverId());
    EXPECT_EQ(car.getModel(), test_car.getModel());
    EXPECT_EQ(car.getNumber(), test_car.getNumber());
    EXPECT_EQ(car.getColor(), test_car.getColor());
    EXPECT_TRUE(car.getCarType() == test_car.getCarType());
}

TEST_F(DriverGetCarTest, ExampleData_2) {
    Driver driver = *model->getDriver(2);
    Car car = driver.getPersonalCars()[0];

    Car test_car = car;
    try {
        Driver* test_driver = model->getDriver(1);
        test_car = (test_driver->getPersonalCars()[0]);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(car.getDriverId(), driver.getId());
    EXPECT_EQ(car.getModel(), "Mazda RX8");
    EXPECT_EQ(car.getNumber(), "O000OO");
    EXPECT_EQ(car.getColor(), "white");
    EXPECT_TRUE(car.getCarType() == CarType::Business);

    // Check data from database
    EXPECT_EQ(car.getDriverId(), test_car.getDriverId());
    EXPECT_EQ(car.getModel(), test_car.getModel());
    EXPECT_EQ(car.getNumber(), test_car.getNumber());
    EXPECT_EQ(car.getColor(), test_car.getColor());
    EXPECT_TRUE(car.getCarType() == test_car.getCarType());
}

TEST_F(DriverGetCarTest, ExampleData_3) {
    Driver driver = *model->getDriver(3);
    Car car = driver.getPersonalCars()[0];

    Car test_car = car;
    try {
        Driver* test_driver = model->getDriver(1);
        test_car = (test_driver->getPersonalCars()[0]);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(car.getDriverId(), driver.getId());
    EXPECT_EQ(car.getModel(), "Nissan GTR GT");
    EXPECT_EQ(car.getNumber(), "V123AZ");
    EXPECT_EQ(car.getColor(), "blue");
    EXPECT_TRUE(car.getCarType() == CarType::Comfort);

    // Check data from database
    EXPECT_EQ(car.getDriverId(), test_car.getDriverId());
    EXPECT_EQ(car.getModel(), test_car.getModel());
    EXPECT_EQ(car.getNumber(), test_car.getNumber());
    EXPECT_EQ(car.getColor(), test_car.getColor());
    EXPECT_TRUE(car.getCarType() == test_car.getCarType());
}

TEST_F(DriverGetCarTest, ExampleData_4) {
    Driver driver = *model->getDriver(4);
    Car car = driver.getPersonalCars()[0];

    Car test_car = car;
    try {
        Driver* test_driver = model->getDriver(1);
        test_car = (test_driver->getPersonalCars()[0]);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(car.getDriverId(), driver.getId());
    EXPECT_EQ(car.getModel(), "hyundai");
    EXPECT_EQ(car.getNumber(), "M532KF");
    EXPECT_EQ(car.getColor(), "blue");
    EXPECT_TRUE(car.getCarType() == CarType::Comfort);

    // Check data from database
    EXPECT_EQ(car.getDriverId(), test_car.getDriverId());
    EXPECT_EQ(car.getModel(), test_car.getModel());
    EXPECT_EQ(car.getNumber(), test_car.getNumber());
    EXPECT_EQ(car.getColor(), test_car.getColor());
    EXPECT_TRUE(car.getCarType() == test_car.getCarType());
}
