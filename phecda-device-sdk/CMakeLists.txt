cmake_minimum_required(VERSION 3.27)
project(phecda_device_sdk)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS "include/**/*")
file(GLOB SOURCES "src/**/*" "src/*")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(phecda_device_sdk STATIC ${HEADERS} ${SOURCES} )


#add_executable(phecda_device_sdk main.cpp DeviceDriverSample.cpp ${SOURCES})
