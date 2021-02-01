cmake_minimum_required(VERSION 3.9)
project(lib_common)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(lib_common STATIC 
			DTO/user.h
			DTO/investments.h 
			DTO/investments.cpp 
			uri.h
			place_holder.cpp)

include_directories(DTO/nlohmaan)