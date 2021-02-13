project(Server)

find_package(cpprestsdk CONFIG REQUIRED) 

if(!MSVC)
    find_package(Boost COMPONENTS filesystem system REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Common/DTO)

set(PROJECT_SOURCES
main.cpp
httpserver.h
httpserver.cpp
userrepository.h 
userrepository.cpp
usermanager.h
usermanager.cpp
usermanager_facade.h
usermanager_facade.cpp
investmentsmanager.h
investmentsmanager.cpp
investmentsmanager_facade.h
investmentsmanager_facade.cpp
investmentsrepository.h
investmentsrepository.cpp
currencyconverter.h
currencyconverter.cpp
)


add_executable(server ${PROJECT_SOURCES})

target_link_libraries(server PRIVATE cpprestsdk::cpprest lib_common)

if(!MSVC)
    target_link_libraries(server PRIVATE boost_system)
endif()