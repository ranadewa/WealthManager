cmake_minimum_required(VERSION 3.9)
project(lib_common)

add_library(lib_common STATIC 
			DTO/user.h
			uri.h
			place_holder.cpp)
