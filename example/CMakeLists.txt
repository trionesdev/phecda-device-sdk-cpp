cmake_minimum_required(VERSION 3.28)
project(example)

set(CMAKE_CXX_STANDARD 14)

add_executable(example main.cpp ../src/cmake-build-debug/libphecda_device_sdk_cpp.a)
