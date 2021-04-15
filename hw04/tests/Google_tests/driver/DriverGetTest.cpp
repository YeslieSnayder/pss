//
// Created by yesliesnayder on 12.04.2021.
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

class DriverGetTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    DriverGetTest() {
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

TEST_F(DriverGetTest, ExampleData_1) {
    Document driver_doc;
    driver_doc.CopyFrom(json["correct"][0]["driver_1"], json.GetAllocator());
    Driver driver(driver_doc);

    Driver* test_driver;
    try {
        test_driver = model->getDriver(1);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(driver.getId(), 1);
    EXPECT_EQ(driver.getName(), "Oleg");
    EXPECT_EQ(driver.getRating(), 5);
    EXPECT_TRUE(driver.getStatus() == DriverStatus::WORKING);

    // Check data from database
    EXPECT_EQ(driver.getId(), test_driver->getId());
    EXPECT_EQ(driver.getName(), test_driver->getName());
    EXPECT_EQ(driver.getRating(), test_driver->getRating());
    EXPECT_TRUE(driver.getStatus() == test_driver->getStatus());

    EXPECT_EQ(driver.getOrderHistory().size(), test_driver->getOrderHistory().size());
    Car first = *driver.getPersonalCar();
    Car second= *driver.getPersonalCar();
    EXPECT_TRUE(first == second);
}

TEST_F(DriverGetTest, ExampleData_2) {
    Document driver_doc;
    driver_doc.CopyFrom(json["correct"][1]["driver_2"], json.GetAllocator());
    Driver driver(driver_doc);

    Driver* test_driver;
    try {
        test_driver = model->getDriver(2);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(driver.getId(), 2);
    EXPECT_EQ(driver.getName(), "Louse");
    EXPECT_EQ(driver.getRating(), 4.2);
    EXPECT_TRUE(driver.getStatus() == DriverStatus::NOT_WORKING);

    // Check data from database
    EXPECT_EQ(driver.getId(), test_driver->getId());
    EXPECT_EQ(driver.getName(), test_driver->getName());
    EXPECT_EQ(driver.getRating(), test_driver->getRating());
    EXPECT_TRUE(driver.getStatus() == test_driver->getStatus());

    EXPECT_EQ(driver.getOrderHistory().size(), test_driver->getOrderHistory().size());
    Car first = *driver.getPersonalCar();
    Car second= *driver.getPersonalCar();
    EXPECT_TRUE(first == second);
}

TEST_F(DriverGetTest, ExampleData_3) {
    Document driver_doc;
    driver_doc.CopyFrom(json["correct"][2]["driver_3"], json.GetAllocator());
    Driver driver(driver_doc);

    Driver* test_driver;
    try {
        test_driver = model->getDriver(3);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(driver.getId(), 3);
    EXPECT_EQ(driver.getName(), "Kirill");
    EXPECT_EQ(driver.getRating(), 3.8);
    EXPECT_TRUE(driver.getStatus() == DriverStatus::IN_RIDE);

    // Check data from database
    EXPECT_EQ(driver.getId(), test_driver->getId());
    EXPECT_EQ(driver.getName(), test_driver->getName());
    EXPECT_EQ(driver.getRating(), test_driver->getRating());
    EXPECT_TRUE(driver.getStatus() == test_driver->getStatus());

    EXPECT_EQ(driver.getOrderHistory().size(), test_driver->getOrderHistory().size());
    Car first = *driver.getPersonalCar();
    Car second= *driver.getPersonalCar();
    EXPECT_TRUE(first == second);
}

TEST_F(DriverGetTest, ExampleData_4) {
    Document driver_doc;
    driver_doc.CopyFrom(json["correct"][3]["driver_4"], json.GetAllocator());
    Driver driver(driver_doc);

    Driver* test_driver;
    try {
        test_driver = model->getDriver(4);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data (taken from file 'driver_data.json')
    EXPECT_EQ(driver.getId(), 4);
    EXPECT_EQ(driver.getName(), "Arthur");
    EXPECT_EQ(driver.getRating(), 4.99);
    EXPECT_TRUE(driver.getStatus() == DriverStatus::IN_RIDE);

    // Check data from database
    EXPECT_EQ(driver.getId(), test_driver->getId());
    EXPECT_EQ(driver.getName(), test_driver->getName());
    EXPECT_EQ(driver.getRating(), test_driver->getRating());
    EXPECT_TRUE(driver.getStatus() == test_driver->getStatus());

    EXPECT_EQ(driver.getOrderHistory().size(), test_driver->getOrderHistory().size());
    Car first = *driver.getPersonalCar();
    Car second= *driver.getPersonalCar();
    EXPECT_TRUE(first == second);
}
