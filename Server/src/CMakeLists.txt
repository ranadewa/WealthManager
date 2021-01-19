project(Server)

find_package(cpprestsdk CONFIG REQUIRED) 

if(!MSVC)
    find_package(Boost COMPONENTS filesystem system REQUIRED)
endif()

set(PROJECT_SOURCES
main.cpp
httpserver.h
httpserver.cpp
)

add_executable(server ${PROJECT_SOURCES})
target_link_libraries(server PRIVATE cpprestsdk::cpprest)

if(!MSVC)
    target_link_libraries(server PRIVATE boost_system)
endif()