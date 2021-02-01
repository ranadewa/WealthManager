cmake_minimum_required(VERSION 3.9)
project(wealth_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(QTClient/Client)