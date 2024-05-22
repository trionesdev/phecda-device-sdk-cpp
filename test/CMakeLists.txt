cmake_minimum_required(VERSION 3.27)
project(SdkTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
include_directories(../third-party/include)
link_directories(../third-party/lib)


add_executable(SdkTest sdk_test.cpp DeviceDriverSample.cpp )
target_link_libraries(SdkTest phecda-device-sdk )

