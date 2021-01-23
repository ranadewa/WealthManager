cmake_minimum_required(VERSION 3.9)
project(wealth_manager)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message("C1 :" ${CMAKE_SOURCE_DIR})
# set(THIRD_PARTY_INSTALL_DIR "${CMAKE_SOURCE_DIR}/Build.3rdParty/Install" CACHE STRING "Directory that contains the built 3rd party libraries.")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake)

# find_package(cpprestsdk CONFIG REQUIRED) 

add_subdirectory(3rdParty)
add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(QTClient/Client)