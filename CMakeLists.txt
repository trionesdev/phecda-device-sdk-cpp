cmake_minimum_required(VERSION 3.28)
project(phecda_device)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(phecda-device-sdk)
#link_directories(src)

add_executable(phecda_device main.cpp DeviceDriverSample.cpp)
target_link_libraries(phecda_device phecda_device_sdk)