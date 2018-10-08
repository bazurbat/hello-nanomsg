cmake_minimum_required(VERSION 3.4)

project(hello-nanomsg)

find_package(Threads REQUIRED)
find_package(nanomsg REQUIRED)
find_package(GTest REQUIRED)

add_executable(nn-server server.c)
target_link_libraries(nn-server nanomsg)

add_executable(nn-client client.c)
target_link_libraries(nn-client nanomsg)

add_executable(reqrep-test reqrep-test.cpp)
target_include_directories(reqrep-test PRIVATE
    ${GTEST_INCLUDE_DIRS})
target_link_libraries(reqrep-test
    Threads::Threads ${GTEST_BOTH_LIBRARIES})

install(TARGETS nn-server nn-client
    DESTINATION bin)
