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

class PassengerGetTest : public ::testing::Test {
protected:
    Database* db{};
    Model* model{};
    Document json;

    PassengerGetTest() {
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

        Document passenger;
        passenger.CopyFrom(json[0], json.GetAllocator());
        model->createPassenger(passenger);
        passenger.CopyFrom(json[1], json.GetAllocator());
        model->createPassenger(passenger);
        passenger.CopyFrom(json[2], json.GetAllocator());
        model->createPassenger(passenger);
        passenger.CopyFrom(json[3], json.GetAllocator());
        model->createPassenger(passenger);
    }

    virtual void TearDown() {
        delete model;
        delete db;
    }
};

TEST_F(PassengerGetTest, DataCorrectness_1) {
    Document doc;
    doc.CopyFrom(json[0], json.GetAllocator());
    Passenger passenger(doc);

    Passenger* test_passenger;
    try {
        test_passenger = model->getPassenger(1);
    } catch (NotFoundException ex) {
        ASSERT_EQ(0, 1);    // Continue another tests, if there was exception
    }

    // Check expecting data
    EXPECT_EQ(passenger.getId(), 1);
    EXPECT_EQ(passenger.getName(), "Jacquelyn");
    EXPECT_FLOAT_EQ(passenger.getRating(), 4.07);
    EXPECT_TRUE(passenger.getPaymentMethod() == PaymentMethod::ONLINE);

    // Check data from database
    EXPECT_EQ(passenger.getId(), test_passenger->getId());
    EXPECT_EQ(passenger.getName(), test_passenger->getName());
    EXPECT_EQ(passenger.getRating(), test_passenger->getRating());
    EXPECT_TRUE(passenger.getPaymentMethod() == test_passenger->getPaymentMethod());

    EXPECT_EQ(passenger.getPinnedAddresses().size(), test_passenger->getPinnedAddresses().size());
    vector<GEOAddress> addresses_original = passenger.getPinnedAddresses();
    vector<GEOAddress> addresses_database = test_passenger->getPinnedAddresses();
    ASSERT_EQ(addresses_original.size(), addresses_database.size());
    for (auto& x : addresses_original) {
        bool flag = false;
        for (auto& y : addresses_database) {
            if (x == y) {
                flag = true;
                break;
            }
        }
        EXPECT_TRUE(flag);
    }
}