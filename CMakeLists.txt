cmake_minimum_required(VERSION 3.27)
project(phecda_device)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(phecda-device-sdk)
#link_directories(src)

include_directories(phecda-device-sdk/include)

file(GLOB HEADERS phecda-device-sdk/include)

add_executable(phecda_device main.cpp DeviceDriverSample.cpp ${HEADERS})
target_link_libraries(phecda_device phecda_device_sdk )