#.rst:
# FindCppRest
# -----------
#
# Find the CppRest library.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module will set the following variables in your project:
#
# ``CppRest_FOUND``
#   System has the CppRest library.
# ``CppRest_OUT_DIR``
#   The output Directory for the CppRest binaries.
# ``CppRest_INCLUDE_DIR``
#   The CppRest include directory.
# ``CppRest_LIBRARY``
#   The CppRest library.
# ``CppRest_ARTIFACT_DEBUG``
#   The full path to the debug version of the Rcpp shared library.
# ``CppRest_ARTIFACT_RELEASE``
#   The full path to the release version of the Rcpp shared library.

message("C2 :" ${CMAKE_SOURCE_DIR}) 
find_path(CppRest_ROOT_DIR include/cpprest/http_client.h 
  HINTS
    ${CMAKE_SOURCE_DIR}/3rdParty/cpprestsdk/Release
)

message("C3 " ${CppRest_ROOT_DIR})
if(CppRest_ROOT_DIR)
  message(STATUS "CppRest root directory ${CppRest_ROOT_DIR}")
  set(CppRest_INCLUDE_DIR ${CppRest_ROOT_DIR}/include)
  message(STATUS "CppRest include directory ${CppRest_INCLUDE_DIR}")

  find_library(CppRest_DEBUG
    cpprestd
    HINTS ${CppRest_ROOT_DIR}/lib
  )

  find_library(CppRest_RELEASE
    cpprest
    HINTS ${CppRest_ROOT_DIR}/lib
  )

  set(CppRest_LIBRARY_DEBUG "${CppRest_DEBUG}")
  set(CppRest_LIBRARY_RELEASE "${CppRest_RELEASE}")

 file(GLOB CppRest_ARTIFACT_RELEASE ${CppRest_ROOT_DIR}/lib/libcpprest.so*)
 file(GLOB CppRest_ARTIFACT_DEBUG ${CppRest_ROOT_DIR}/lib/libcpprestd.so*)

  # Define CppRest_LIBRARY
  include(SelectLibraryConfigurations)
  select_library_configurations(CppRest)

  mark_as_advanced(CppRest_LIBRARY_DEBUG, CppRest_LIBRARY_RELEASE)


endif(CppRest_ROOT_DIR)

message(${CppRest_LIBRARY})

message(${CppRest_LIBRARY_DEBUG})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppRest DEFAULT_MSG CppRest_INCLUDE_DIR CppRest_LIBRARY)

mark_as_advanced(CppRest_INCLUDE_DIR CppRest_LIBRARY CppRest_ARTIFACT_RELEASE CppRest_ARTIFACT_DEBUG)
