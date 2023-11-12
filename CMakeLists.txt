cmake_minimum_required(VERSION 3.20)
project(gralph
        VERSION 0.1.0
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

add_subdirectory(src)
add_subdirectory(tests)

target_include_directories(gralph PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_executable(main graph-lib.cpp)
target_link_libraries(main PUBLIC gralph)

include(CTest)
enable_testing()
add_test(NAME gralphTests COMMAND gralphTests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
