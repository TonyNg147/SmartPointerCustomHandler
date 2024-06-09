cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(util/Base)
add_subdirectory(util/PermissionForHeap)
add_subdirectory(util/SmartPtr)

set(ENABLE_TEST ON)

if (ENABLE_TEST)
    add_subdirectory(test)
endif()

