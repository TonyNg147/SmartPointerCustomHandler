cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

project(TestPtr)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)

include(BuildScript/WrapTestBuilt.cmake)

WrapBuilt(
    BuiltName TestSharedPtr
    Sources TestSharedPtr.cpp
)

WrapBuilt(
    BuiltName TestWeakPtr
    Sources TestWeakPtr.cpp
)
