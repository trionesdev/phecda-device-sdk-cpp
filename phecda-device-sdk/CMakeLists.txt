cmake_minimum_required(VERSION 3.27)
project(phecda-device-sdk)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS "include/**/*")
file(GLOB SOURCES "src/**/*" "src/*")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/include)

set(LINK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party/lib)

link_directories(${LINK_DIR})

add_library(phecda-device-sdk STATIC ${HEADERS} ${SOURCES})

target_link_libraries(phecda-device-sdk libyaml-cppd.a)
#add_executable(phecda_device_sdk main.cpp DeviceDriverSample.cpp ${SOURCES})
