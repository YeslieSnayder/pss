//
// Created by yesliesnayder on 11.04.2021.
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

class DriverLoginTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    DriverLoginTest() {
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
    }

    virtual void TearDown() {
        delete model;
        delete db;
    }
};

TEST_F(DriverLoginTest, ExampleData) {
    try {
        Document driver;
        driver.CopyFrom(json["correct"][0]["driver_1"], json.GetAllocator());
        unsigned long int id = model->createDriver(driver);
        EXPECT_EQ(id, 1);

        driver.CopyFrom(json["correct"][1]["driver_2"], json.GetAllocator());
        unsigned long int id2 = model->createDriver(driver);
        EXPECT_EQ(id2, 2);

        EXPECT_LT(id, id2);
    } catch (IncorrectDataException& e) {
        cerr << e.what() << endl;
    }
}

TEST_F(DriverLoginTest, MissingData) {
    Document driver;
    driver.CopyFrom(json["incorrect"][0]["driver_1"], json.GetAllocator());
    EXPECT_THROW({
                     try {
                         unsigned long int id = model->createDriver(driver);
                         ASSERT_NE(id, 1);
                     } catch (IncorrectDataException& e) {
                         auto arr = e.getErrors();
                         ASSERT_EQ(4, arr.size());
                         EXPECT_EQ("name", arr[0].key);
                         EXPECT_EQ("rating", arr[1].key);
                         EXPECT_EQ("personal_cars", arr[2].key);
                         EXPECT_EQ("driver_status", arr[3].key);
                         throw;
                     }
                 }, IncorrectDataException);
}

TEST_F(DriverLoginTest, IncorrectDataTypes) {
    Document driver;
    driver.CopyFrom(json["incorrect"][1]["driver_2"], json.GetAllocator());
    EXPECT_THROW({
                     try {
                         unsigned long int id = model->createDriver(driver);
                         ASSERT_NE(id, 1);
                     } catch (IncorrectDataException& e) {
                         auto arr = e.getErrors();
                         ASSERT_EQ(5, arr.size());
                         EXPECT_EQ("name", arr[0].key);
                         EXPECT_EQ("rating", arr[1].key);
                         EXPECT_EQ("personal_cars", arr[2].key);
                         EXPECT_EQ("driver_status", arr[3].key);
                         EXPECT_EQ("driver_id", arr[4].key);
                         throw;
                     }
                 }, IncorrectDataException);
}

TEST_F(DriverLoginTest, IncorrectData) {
    Document driver;
    driver.CopyFrom(json["incorrect"][2]["driver_3"], json.GetAllocator());
    EXPECT_THROW({
                     try {
                         unsigned long int id = model->createDriver(driver);
                         ASSERT_NE(id, 1);
                     } catch (IncorrectDataException& e) {
                         auto arr = e.getErrors();
                         ASSERT_EQ(3, arr.size());
                         EXPECT_EQ("name", arr[0].key);
                         EXPECT_EQ("rating", arr[1].key);
                         EXPECT_EQ("driver_status", arr[2].key);
                         throw;
                     }
                 }, IncorrectDataException);
}
