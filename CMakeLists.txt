cmake_minimum_required(VERSION 3.27)
project(phecda-device-sdk)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(test)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/**/*")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/**/*" "${PROJECT_SOURCE_DIR}/src/*")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/include)

set(LINK_DIR ${PROJECT_SOURCE_DIR}/third-party/lib)

link_directories(${LINK_DIR})

add_library(phecda-device-sdk STATIC ${HEADERS} ${SOURCES}
        include/phecda/IDeviceServiceSDK.h)

target_link_libraries(phecda-device-sdk PRIVATE  libyaml-cppd.a)
