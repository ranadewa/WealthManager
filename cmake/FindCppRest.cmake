

include(GNUInstallDirs) 

find_library(
  CppRest_LIBRARY 
  NAMES libcpprest
  HINTS ${PROJECT_BINARY_DIR}/3rdParty/cpprestsdk/Release/Binaries/
)
 
find_path(CppRest_ROOT_DIR include/cpprest/http_client.h 
  HINTS
    ${CMAKE_SOURCE_DIR}/3rdParty/cpprestsdk/Release/Binaries
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppRest DEFAULT_MSG CppRest_INCLUDE_DIR CppRest_LIBRARY)

mark_as_advanced(CppRest_INCLUDE_DIR CppRest_LIBRARY CppRest_ARTIFACT_RELEASE CppRest_ARTIFACT_DEBUG)


