cmake_minimum_required(VERSION 3.28)
project(phecda_device_sdk)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/**/*")

add_library(phecda_device_sdk STATIC ${SOURCES})
