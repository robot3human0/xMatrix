cmake_minimum_required(VERSION 3.14)

project(xMatrix VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(xmatrix src/xmatrix.cc)

target_include_directories(xmatrix INTERFACE src)

find_package(GTest REQUIRED)

add_executable(xmatrix_test tests/tests.cc)

target_link_libraries(xmatrix_test
        xmatrix
        GTest::GTest
        GTest::Main
)

enable_testing()

add_test(NAME xmatrix_tests COMMAND xmatrix_test)