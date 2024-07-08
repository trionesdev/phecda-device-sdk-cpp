cmake_minimum_required(VERSION 3.27)
project(phecda-device-sdk)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/**/*")
#file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*/*/*" "${PROJECT_SOURCE_DIR}/src/**/*" "${PROJECT_SOURCE_DIR}/src/*")
#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(log4cxx REQUIRED)
find_package(PahoMqttCpp REQUIRED)

add_library(phecda-device-sdk STATIC ${HEADERS} ${SOURCES} )

#file(GLOB STATIC_LIBS "${LIB_DIR}/*.a")
target_link_libraries(phecda-device-sdk PRIVATE boost::boost yaml-cpp::yaml-cpp nlohmann_json::nlohmann_json log4cxx PahoMqttCpp::paho-mqttpp3-static)
