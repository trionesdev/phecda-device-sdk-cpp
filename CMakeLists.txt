cmake_minimum_required(VERSION 3.27)
project(phecda-device-sdk)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_definitions( -D_WIN32_WINNT=0x0A00 )

add_subdirectory(test)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/**/*")
#file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*/*/*" "${PROJECT_SOURCE_DIR}/src/**/*" "${PROJECT_SOURCE_DIR}/src/*")
#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/third-party/include)
#
#
#
#if(CMAKE_SYSTEM_NAME MATCHES "Linux")
#    set(LIB_DIR ${PROJECT_SOURCE_DIR}/third-party/lib/linux)
#elseif (MAKE_SYSTEM_NAME MATCHES "Windows")
#    set(LIB_DIR ${PROJECT_SOURCE_DIR}/third-party/lib/win)
#elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
#    set(LIB_DIR ${PROJECT_SOURCE_DIR}/third-party/lib/osx)
#else ()
#endif ()

#link_directories(${LIB_DIR})

find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(phecda-device-sdk STATIC ${HEADERS} ${SOURCES} )

#file(GLOB STATIC_LIBS "${LIB_DIR}/*.a")
target_link_libraries(phecda-device-sdk PRIVATE boost::boost yaml-cpp::yaml-cpp nlohmann_json::nlohmann_json)
