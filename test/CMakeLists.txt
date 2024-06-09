cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

project(TestPtr)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)

qt_add_executable(${PROJECT_NAME}
    TestSharedPtr.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SmartPtr
        Qt6::Core
        Qt6::Gui
        Qt6::Test
        Qt6::Widgets
)
