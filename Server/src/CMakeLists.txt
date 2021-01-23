project(Server)



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/cpprestsdk/Release/include)

set(PROJECT_SOURCES
main.cpp
httpserver.h
httpserver.cpp
usermanager.h
usermanager.cpp
usermanager_facade.h
usermanager_facade.cpp
)


add_executable(server ${PROJECT_SOURCES})

target_link_libraries(server PRIVATE  cpprestsdk lib_common)

if(!MSVC)
    target_link_libraries(server PRIVATE boost_system)
endif()