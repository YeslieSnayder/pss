project(WendexTaxi)

# SQLite database -> does not work
#set(SQLite_DIR include/sqlite3)
#find_package(SQLite3)
#include_directories(include/sqlite3)
#target_link_libraries(${PROJECT_NAME} LINK_PUBLIC sqlite3)

# PostgreSQL -> does not work
#find_package(PostgreSQL REQUIRED)
#target_include_directories(${PROJECT_NAME} PRIVATE ${PostgreSQL_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PostgreSQL_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)
#set(PostgreSQL_TYPE_INCLUDE_DIR "${PostgreSQL_TYPE_INCLUDE_DIR};/usr/include/postgresql/")
#set(PostgreSQL_TYPE_INCLUDE_DIR "${PostgreSQL_TYPE_INCLUDE_DIR} /include/postgresql-13.2/")

# Pistache build
set(PISTACHE_DIR include/pistache)
include_directories(${PISTACHE_DIR}/include)

# Start the program
add_executable(${PROJECT_NAME} application/api/main.cpp)
target_link_libraries(${PROJECT_NAME} pistache -lpthread)

# Google Tests
add_subdirectory(tests/Google_tests)