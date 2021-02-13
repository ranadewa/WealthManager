cmake_minimum_required(VERSION 3.5)

project(Client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  message(STATUS "Building from qt client from main project.")
else()
  message(STATUS "Building from QT creator")
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Common ${CMAKE_CURRENT_BINARY_DIR}/CommonDuplicate)
endif()


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID) 
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Common/DTO)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        utils.h
        utils.cpp
        overview.cpp
        overview.h
        investmentstab.h
        investmentstab.cpp
        constants.h
        mainwindow.ui
        loginwindow.h
        loginwindow.cpp
        loginwindow.ui
        changepassword.h
        changepassword.cpp
        changepassword.ui
        addnewuser.h
        addnewuser.cpp
        addnewuser.ui
        newinvestment.cpp
        newinvestment.h
        newinvestment.ui
        errordialog.cpp
        errordialog.h
        errordialog.ui
        confirmationdialog.cpp
        confirmationdialog.h
        confirmationdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Client
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Client
            ${PROJECT_SOURCES}
        )
    endif()
endif()
message("QT VERSION:: " ${QT_VERSION_MAJOR})
# find_library(lib_common ${CMAKE_CURRENT_SOURCE_DIR}/../Common)
# target_link_directories (lib_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Common)
target_link_libraries(Client PUBLIC lib_common)
target_link_libraries(Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Network)

