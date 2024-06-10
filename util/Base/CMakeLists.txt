cmake_minimum_required(VERSION 3.16)

project(Base)

set(SOURCES Interface.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES}
    TypeHelpers.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)
