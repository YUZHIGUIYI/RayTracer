cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(RayTracer LANGUAGES CXX C)

option(BUILD_RELEASE "CMake build type: Release" ON)
if(BUILD_RELEASE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "CMake build type: Release")
else()
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "CMake build type: Debug")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_subdirectory(OneWeekend)
add_subdirectory(OneWeek)
add_subdirectory(RayTracerApp)
