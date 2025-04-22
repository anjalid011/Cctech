# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GeometryApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GeometryApp_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\geometry_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\geometry_autogen.dir\\ParseCache.txt"
  "GeometryApp_autogen"
  "geometry_autogen"
  )
endif()
