# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\geometry_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\geometry_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\main_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\main_autogen.dir\\ParseCache.txt"
  "geometry_autogen"
  "main_autogen"
  )
endif()
