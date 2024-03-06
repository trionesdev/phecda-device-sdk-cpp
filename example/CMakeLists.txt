cmake_minimum_required(VERSION 3.28)
project(example)

set(CMAKE_CXX_STANDARD 14)

link_directories(../src/cmake-build-debug)

add_executable(example main.cpp)
target_link_libraries(example libphecda_device_sdk_cpp.a)