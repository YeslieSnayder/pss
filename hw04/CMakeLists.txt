project(WendexTaxi)

# Pistache build
set(PISTACHE_DIR include/pistache)
include_directories(${PISTACHE_DIR}/include)

# Start the program
add_executable(${PROJECT_NAME} application/api/main.cpp)

target_link_libraries(${PROJECT_NAME} pistache -lpthread)

# Google Tests
#add_subdirectory(tests/Google_tests)