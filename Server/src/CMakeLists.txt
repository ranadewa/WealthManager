project(Server)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable(server main.cpp)
target_link_libraries(server PRIVATE cpprestsdk::cpprest)