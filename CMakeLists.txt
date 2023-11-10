cmake_minimum_required(VERSION 3.20)
project(gralph
        VERSION 0.1.0
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_library(gralph ${SOURCES} ${HEADERS})

target_include_directories(gralph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(gralph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Graphs graph-lib.cpp)

target_link_libraries(Graphs PRIVATE gralph)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
