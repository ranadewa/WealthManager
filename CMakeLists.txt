cmake_minimum_required(VERSION 3.9)
project(wealth_manager)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(CppRest REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(QTClient/Client)