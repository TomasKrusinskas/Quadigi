cmake_minimum_required(VERSION 3.10)
project(QuadigiTests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(TestCalculator TestCalculator.cpp)
target_link_libraries(TestCalculator gtest gtest_main)

add_test(NAME CalculatorTests COMMAND TestCalculator)