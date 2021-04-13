project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run targets
add_executable(Google_Tests_run DriverLoginTest.cpp DriverGetTest.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)
