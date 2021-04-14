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

class DriverPatchTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    DriverPatchTest() {
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

TEST_F(DriverPatchTest, PatchAllData) {
    Document driver_doc;
    driver_doc.CopyFrom(json["correct"][0]["driver_1"], json.GetAllocator());
    Driver driver(driver_doc);

    // Test data
    string name{"Andrey"};
    double rating{4.91};
    DriverStatus status{DriverStatus::NOT_WORKING};

    // Check non-repetitive data
    EXPECT_NE(name, driver.getName());
    EXPECT_NE(rating, driver.getRating());
    EXPECT_FALSE(status == driver.getStatus());

    driver.setName(name);
    driver.setRating(rating);
    driver.setStatus(status);

    EXPECT_EQ(name, driver.getName());
    EXPECT_EQ(rating, driver.getRating());
    EXPECT_TRUE(status == driver.getStatus());
}