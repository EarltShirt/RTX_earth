cmake_minimum_required(VERSION 3.10)
project(RTX_earth VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Specify the path to the curl and libzip installation directories
set(CURL_ROOT "D:/repos/vcpkg/installed/x64-windows")
set(LIBZIP_ROOT "D:/repos/vcpkg/installed/x64-windows")

find_package(CURL CONFIG REQUIRED)
find_package(LibZip CONFIG REQUIRED)
include_directories(include)
include_directories(D:/repos/vcpkg/installed/x64-windows/include/curl)
include_directories(D:/repos/vcpkg/installed/x64-windows/include/zip)

add_executable(RTX_earth src/main.cpp src/load.cpp src/unzip.cpp src/HeightMap.cpp)
target_link_libraries(RTX_earth PRIVATE CURL::libcurl libzip::zip)