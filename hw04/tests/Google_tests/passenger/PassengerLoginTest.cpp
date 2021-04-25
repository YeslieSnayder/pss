//
// Created by yesliesnayder on 25.04.2021.
//

#include "gtest/gtest.h"

#include "../../../application/db/TestDatabase.h"
#include "../../../application/model/model.h"
#include "../../../application/view/logger.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

class PassengerLoginTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    PassengerLoginTest() {
        ifstream ifs{R"(tests/json_data/passengers.json)"};
        if ( !ifs.is_open() )
        {
            log(LOG::ERROR, "Could not open file for reading!");
            throw exception();
        }

        IStreamWrapper isw{ifs};
        json.ParseStream(isw);

        StringBuffer buffer{};
        Writer<StringBuffer> writer{buffer};
        json.Accept(writer);

        if ( json.HasParseError() )
        {
            log(LOG::ERROR, to_string(json.GetParseError()));
            log(LOG::ERROR, "Offset : " + to_string(json.GetErrorOffset()));
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

TEST_F(PassengerLoginTest, SetId) {
    try {
        Document passenger;
        passenger.CopyFrom(json[0], json.GetAllocator());
        unsigned long int id = model->createPassenger(passenger);
        EXPECT_EQ(id, 1);

        passenger.CopyFrom(json[1], json.GetAllocator());
        unsigned long int id2 = model->createPassenger(passenger);
        EXPECT_EQ(id2, 2);

        EXPECT_LT(id, id2);
    } catch (IncorrectDataException& e) {
        log(LOG::ERROR, e.what());
    }
}