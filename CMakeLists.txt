#This Phoenix CMakeLists 
cmake_minimum_required (VERSION 3.0)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(lib)
add_subdirectory(source)
add_subdirectory(tools)
