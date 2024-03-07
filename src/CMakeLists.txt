cmake_minimum_required(VERSION 3.28)
project(phecda_device_sdk)

set(CMAKE_CXX_STANDARD 14)

add_library(phecda_device_sdk STATIC library.cpp
        protocol_driver.h
        device_service_sdk.cpp
        device_service_sdk.h
)
