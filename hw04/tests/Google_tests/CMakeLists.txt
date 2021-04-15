project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run targets
add_executable(Google_Tests_run main_test.cpp driver/DriverLoginTest.cpp driver/DriverGetTest.cpp driver/DriverPatchTest.cpp driver/DriverAcceptOrderTest.cpp driver/DriverOrderHistoryTest.cpp driver/DriverGetCarTest.cpp driver/DriverGetAvailableOrdersTest.cpp driver/DriverCompleteOrderTest.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)
