cmake_minimum_required(VERSION 3.31)
project(rpn_calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_SANITIZER "address")
set(CMAKE_CXX_SANITIZER "undefined")

add_library(rpn_calculator STATIC src/rpn.cpp)

target_include_directories(rpn_calculator
        PRIVATE
        src/rpn.cpp
        PUBLIC
        include/Stack.hpp
        include/rpn.hpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(rpn_tests tests/rpn_tests.cpp)

target_link_libraries(rpn_tests PRIVATE gtest_main rpn_calculator)

include(GoogleTest)
gtest_discover_tests(rpn_tests)