cmake_minimum_required(VERSION 3.10)
project(RTX_earth VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

# Specify the path to the curl installation directory
set(CURL_ROOT "D:/repos/vcpkg/installed/x64-windows")

find_package(CURL CONFIG REQUIRED)
include_directories(include)
add_executable(RTX_earth src/main.cpp src/load.cpp)
target_link_libraries(RTX_earth PRIVATE CURL::libcurl)
