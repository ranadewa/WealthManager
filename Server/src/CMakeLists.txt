project(Server)

find_package(cpprestsdk CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)

add_executable(server main.cpp)
target_link_libraries(server PRIVATE boost_system cpprestsdk::cpprest)