project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run targets
set(DRIVER_TEST driver/DriverLoginTest.cpp driver/DriverGetTest.cpp driver/DriverPatchTest.cpp driver/DriverAcceptOrderTest.cpp driver/DriverOrderHistoryTest.cpp driver/DriverGetCarTest.cpp driver/DriverGetAvailableOrdersTest.cpp driver/DriverCompleteOrderTest.cpp)
set(PASSENGER_TEST passenger/PassengerLoginTest.cpp passenger/PassengerGetTest.cpp)

add_executable(Google_Tests_run main_test.cpp ${DRIVER_TEST} ${PASSENGER_TEST})

target_link_libraries(Google_Tests_run gtest gtest_main)
