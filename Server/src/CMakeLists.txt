project(Server)

find_package(cpprestsdk CONFIG REQUIRED) 

if(!MSVC)
    find_package(Boost COMPONENTS filesystem system REQUIRED)
endif()

add_executable(server main.cpp)
target_link_libraries(server PRIVATE cpprestsdk::cpprest)

if(!MSVC)
    target_link_libraries(server PRIVATE boost_system)
endif()