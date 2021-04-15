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

class DriverGetAvailableOrdersTest : public ::testing::Test {
    void readDrivers();
    void readOrders();
protected:
    Database* db{};
    Model* model{};
    Document driver_json;
    Document order_json;

    DriverGetAvailableOrdersTest() {
        readDrivers();
        readOrders();
    }

    virtual void SetUp() {
        db = new TestDatabase();
        model = new Model(db);

        Document data;
        data.CopyFrom(driver_json["correct"][0]["driver_1"], driver_json.GetAllocator());
        model->createDriver(data);
        data.CopyFrom(driver_json["correct"][1]["driver_2"], driver_json.GetAllocator());
        model->createDriver(data);
        data.CopyFrom(driver_json["correct"][2]["driver_3"], driver_json.GetAllocator());
        model->createDriver(data);
        data.CopyFrom(driver_json["correct"][3]["driver_4"], driver_json.GetAllocator());
        model->createDriver(data);

        data.CopyFrom(order_json["correct"][0]["order_1"], order_json.GetAllocator());
        model->createOrder(data);
        data.CopyFrom(order_json["correct"][1]["order_2"], order_json.GetAllocator());
        model->createOrder(data);
        data.CopyFrom(order_json["correct"][2]["order_3"], order_json.GetAllocator());
        model->createOrder(data);
        data.CopyFrom(order_json["correct"][3]["order_4"], order_json.GetAllocator());
        model->createOrder(data);
        data.CopyFrom(order_json["correct"][4]["order_5"], order_json.GetAllocator());
        model->createOrder(data);
    }

    virtual void TearDown() {
        delete model;
        delete db;
    }
};

void DriverGetAvailableOrdersTest::readDrivers() {
    ifstream ifs{R"(tests/Google_tests/data/driver_data.json)"};
    if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        throw exception();
    }

    IStreamWrapper isw{ifs};
    driver_json.ParseStream(isw);

    StringBuffer buffer{};
    Writer<StringBuffer> writer{buffer};
    driver_json.Accept(writer);

    if (driver_json.HasParseError())
    {
        std::cout << "Error  : " << driver_json.GetParseError()  << '\n'
                  << "Offset : " << driver_json.GetErrorOffset() << '\n';
        throw exception();
    }
}

void DriverGetAvailableOrdersTest::readOrders() {
    ifstream ifs{R"(tests/Google_tests/data/order_data.json)"};
    if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        throw exception();
    }

    IStreamWrapper isw{ifs};
    order_json.ParseStream(isw);

    StringBuffer buffer{};
    Writer<StringBuffer> writer{buffer};
    order_json.Accept(writer);

    if (order_json.HasParseError())
    {
        std::cout << "Error  : " << order_json.GetParseError()  << '\n'
                  << "Offset : " << order_json.GetErrorOffset() << '\n';
        throw exception();
    }
}

TEST_F(DriverGetAvailableOrdersTest, ExampleData) {
    vector<Order> orders = model->getAvailableOrders();
    ASSERT_EQ(orders.size(), 3);

    Document data;
    Order order = orders[0];
    Order* test_order;

    data.CopyFrom(order_json["correct"][0]["order_1"], order_json.GetAllocator());
    test_order = new Order(data);
    EXPECT_TRUE(order == *test_order);

    data.CopyFrom(order_json["correct"][1]["order_2"], order_json.GetAllocator());
    order = orders[1];
    test_order = new Order(data);
    EXPECT_TRUE(order == *test_order);

    data.CopyFrom(order_json["correct"][2]["order_3"], order_json.GetAllocator());
    order = orders[2];
    test_order = new Order(data);
    EXPECT_TRUE(order == *test_order);
}