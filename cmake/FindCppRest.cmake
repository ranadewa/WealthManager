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
    ${CMAKE_SOURCE_DIR}/CppRestSdk
)

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

  if(WIN32)
    file(GLOB CppRest_ARTIFACT_RELEASE ${CppRest_ROOT_DIR}/bin/cpprest.dll)
    file(GLOB CppRest_ARTIFACT_DEBUG ${CppRest_ROOT_DIR}/bin/cpprestd.dll)
  elseif(UNIX)
    file(GLOB CppRest_ARTIFACT_RELEASE ${CppRest_ROOT_DIR}/lib/libcpprest.so*)
    file(GLOB CppRest_ARTIFACT_DEBUG ${CppRest_ROOT_DIR}/lib/libcpprestd.so*)
  endif()
  
  # Define CppRest_LIBRARY
  include(SelectLibraryConfigurations)
  select_library_configurations(CppRest)

  mark_as_advanced(CppRest_LIBRARY_DEBUG, CppRest_LIBRARY_RELEASE)

  if(WIN32)
    # Set boost, openssl, zlib path
    set(BOOST_INCLUDEDIR ${CppRest_ROOT_DIR}/boost/include)
    set(BOOST_LIBRARYDIR ${CppRest_ROOT_DIR}/boost/boost_libs)
  
    set(OPENSSL_ROOT_DIR ${CppRest_ROOT_DIR}/openssl)
    set(ZLIB_ROOT ${CppRest_ROOT_DIR}/zlib)
  endif(WIN32)

endif(CppRest_ROOT_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppRest DEFAULT_MSG CppRest_INCLUDE_DIR CppRest_LIBRARY)

mark_as_advanced(CppRest_INCLUDE_DIR CppRest_LIBRARY CppRest_ARTIFACT_RELEASE CppRest_ARTIFACT_DEBUG)
