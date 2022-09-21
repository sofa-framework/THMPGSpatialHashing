cmake_minimum_required(VERSION 3.12)
project(THMPGSpatialHashing VERSION 0.1)

set(THMPGSPATIALHASHING_SRC_DIR src/THMPGSpatialHashing)

set(HEADER_FILES
    ${THMPGSPATIALHASHING_SRC_DIR}/THMPGHashTable.h
    ${THMPGSPATIALHASHING_SRC_DIR}/THMPGSpatialHashing.h
    ${THMPGSPATIALHASHING_SRC_DIR}/config.h.in
)

set(SOURCE_FILES
    ${THMPGSPATIALHASHING_SRC_DIR}/THMPGHashTable.cpp
    ${THMPGSPATIALHASHING_SRC_DIR}/THMPGSpatialHashing.cpp
    ${THMPGSPATIALHASHING_SRC_DIR}/initTHMPGSpatialHashingPlugin.cpp
)

find_package(Sofa.Config REQUIRED)
sofa_find_package(Sofa.Component.Collision.Detection.Algorithm REQUIRED)
sofa_find_package(Sofa.Component.Collision.Detection.Intersection REQUIRED)
sofa_find_package(CollisionOBBCapsule QUIET)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Sofa.Component.Collision.Detection.Algorithm Sofa.Component.Collision.Detection.Intersection)

if(CollisionOBBCapsule_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC CollisionOBBCapsule)
endif()

find_package(SofaTest QUIET)
if(SofaTest_FOUND)
    add_subdirectory(THMPGSpatialHashing_test)
endif()

sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${PROJECT_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR ${PROJECT_NAME}
    EXAMPLE_INSTALL_DIR "examples"
    RELOCATABLE "plugins"
)