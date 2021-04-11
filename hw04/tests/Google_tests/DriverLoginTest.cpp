//
// Created by yesliesnayder on 11.04.2021.
//

#include "gtest/gtest.h"

#include <iostream>
#include <fstream>

#include "../../application/db/TestDatabase.h"
#include "../../application/model/model.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace rapidjson;
using namespace std;

class DriverLoginTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    DriverLoginTest() {
        ifstream ifs{R"(tests/Google_tests/data/driver_login_data.json)"};
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
    }

    virtual void TearDown() {
        delete model;
        delete db;
    }
};

TEST_F(DriverLoginTest, ExampleData) {
    Document driver;
    driver.CopyFrom(json["correct"][0], json.GetAllocator());
    ASSERT_TRUE(driver.HasMember("driver_1"));

    unsigned long int id = model->createDriver(driver);
    EXPECT_EQ(id, 1);

    driver.CopyFrom(json["correct"][1], json.GetAllocator());
    ASSERT_TRUE(driver.HasMember("driver_2"));

    unsigned long int id2 = model->createDriver(driver);
    EXPECT_EQ(id2, 2);

    EXPECT_LT(id, id2);
}

TEST_F(DriverLoginTest, MissingData) {
    // FIXME: Complete this method
    Document passenger;
    passenger.CopyFrom(json["correct"][0], json.GetAllocator());
    ASSERT_TRUE(passenger.HasMember("driver_1"));

    try {
        unsigned long int id = model->createDriver(passenger);
        EXPECT_EQ(id, 1);
    } catch (exception e) {

    }
}