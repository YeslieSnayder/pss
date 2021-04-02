cmake_minimum_required(VERSION 3.17)
project(pss)

set(CMAKE_CXX_STANDARD 20)
set(PISTACHE_DIR hw04/include/pistache)

include_directories(${PISTACHE_DIR}/include)

add_executable(${PROJECT_NAME} hw04/application/api/main.cpp)

target_link_libraries(${PROJECT_NAME} pistache -lpthread)
