cmake_minimum_required(VERSION 3.12)

project(THMPGSpatialHashing_test)

set(SOURCE_FILES
    THMPGSpatialHashingTest.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} THMPGSpatialHashing SofaTest SofaGTestMain SofaMiscCollision)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
