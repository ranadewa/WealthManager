

include(GNUInstallDirs) 

message("Source Dir: " ${CMAKE_SOURCE_DIR})
find_library(
  CppRest_LIBRARY 
  NAMES libcpprest.so
  HINTS ${CMAKE_SOURCE_DIR}/3rdParty/build/cpprestsdk/Release/Binaries/
)
 
find_path(CppRest_INCLUDE_DIR include/cpprest/http_client.h 
  HINTS
    ${CMAKE_SOURCE_DIR}/3rdParty/cpprestsdk/Release
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppRest DEFAULT_MSG CppRest_INCLUDE_DIR CppRest_LIBRARY)

mark_as_advanced(CppRest_INCLUDE_DIR CppRest_LIBRARY CppRest_ARTIFACT_RELEASE CppRest_ARTIFACT_DEBUG)


if(CppRest_FOUND AND NOT TARGET CppRest::CppRest)
  add_library(CppRest::CppRest SHARED IMPORTED)
  set_target_properties(
    CppRest::CppRest
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CppRest_INCLUDE_DIR}"
      IMPORTED_LOCATION ${CppRest_LIBRARY})
endif()