
project(cpprestsdk)

set(BUILD_TESTS OFF CACHE INTERNAL "overwrite cpprestSDK value")
set(BUILD_SAMPLES OFF CACHE INTERNAL "overwrite cpprestSDK value")

add_subdirectory(src/Release)

# Overwrite OUTPUT_NAME set directly in cpprestsdk, which contains the version numbers
set_target_properties(cpprest PROPERTIES
  OUTPUT_NAME "cpprest"
  DEBUG_POSTFIX "d"
) 

add_subdirectory(cpprestsdk)