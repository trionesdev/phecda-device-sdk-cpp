cmake_minimum_required(VERSION 3.27)
project(phecda-device-sdk)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(test)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/**/*")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/**/*" "${PROJECT_SOURCE_DIR}/src/*")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/include)



if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/third-party/lib/linux)
elseif (MAKE_SYSTEM_NAME MATCHES "Windows")
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/third-party/lib/win)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/third-party/lib/osx)
else ()
endif ()

link_directories(${LIB_DIR})

add_library(phecda-device-sdk STATIC ${HEADERS} ${SOURCES} )

file(GLOB STATIC_LIBS "${LIB_DIR}/*.a")
target_link_libraries(phecda-device-sdk PRIVATE ${STATIC_LIBS})
