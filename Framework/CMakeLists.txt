cmake_minimum_required(VERSION 3.10)
project(GeometryFramework)

# Set the C++ compiler and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Enable Qt support
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/application)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/geometry/include)

# Source files for the geometry shared library
file(GLOB GEOMETRY_SRC 
    ${CMAKE_SOURCE_DIR}/geometry/src/Conversions/*.cpp
    ${CMAKE_SOURCE_DIR}/geometry/src/Shapes/*.cpp
)

# Application source files
set(APPLICATION_SRC
    ${CMAKE_SOURCE_DIR}/application/main.cpp
    ${CMAKE_SOURCE_DIR}/application/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/application/mainwindow.h
    ${CMAKE_SOURCE_DIR}/application/mainwindow.ui
    ${CMAKE_SOURCE_DIR}/application/openglwidget.cpp
    ${CMAKE_SOURCE_DIR}/application/openglwidget.h
)

# Set Qt installation path if needed
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64")

# Find required Qt components
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

# Add the geometry shared library
add_library(geometry SHARED ${GEOMETRY_SRC})
target_link_libraries(geometry Qt6::Widgets)

# Add the main application executable
add_executable(GeometryApp ${APPLICATION_SRC})
target_link_libraries(GeometryApp geometry Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets opengl32)
