cmake_minimum_required(VERSION 3.10)
project(Calculator VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Calculator src/main.cpp)

include(CTest)
enable_testing()
