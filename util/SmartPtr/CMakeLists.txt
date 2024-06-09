cmake_minimum_required(VERSION 3.16)

project(SmartPtr)

set(SOURCES SharedPtr.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        Base
        Util
)
