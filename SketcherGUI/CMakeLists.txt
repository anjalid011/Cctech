cmake_minimum_required(VERSION 3.10)
project(SketcherProject)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
 
 

# Include directories
set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/geometry/include
    ${CMAKE_SOURCE_DIR}/application
    ${CMAKE_SOURCE_DIR}/external
)
 
include_directories(${INCLUDE_DIRECTORIES})
 
# Source files
file(GLOB GEOMETRY_SRC ${CMAKE_SOURCE_DIR}/geometry/src/*.cpp)
file(GLOB APPLICATION_SRC
    ${CMAKE_SOURCE_DIR}/application/src/mainWindow.cpp
    ${CMAKE_SOURCE_DIR}/application/include/mainWindow.h
    ${CMAKE_SOURCE_DIR}/application/src/Conversion/*.cpp
    ${CMAKE_SOURCE_DIR}/application/src/Shapes/*.cpp
    ${CMAKE_SOURCE_DIR}/application/ui/*.ui
)
 
 
# Find Qt
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)
 
# Add shared library (no MainWindow.cpp here unless really needed)
add_library(geometry SHARED ${GEOMETRY_SRC})
target_link_libraries(geometry Qt6::Widgets)
 
# Add executable
add_executable(main ${APPLICATION_SRC} "application/src/mainWindow.cpp")
target_link_libraries(main geometry Qt6::Widgets Qt6::OpenGLWidgets)