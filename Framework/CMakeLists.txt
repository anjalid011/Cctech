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
include_directories("C:/Users/Anjali Dongare/Desktop/Project/boost_1_88_0")
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
    ${CMAKE_SOURCE_DIR}/application/openglwidget.cpp
    ${CMAKE_SOURCE_DIR}/application/openglwidget.h
    ${CMAKE_SOURCE_DIR}/Extrusion/include/Extrusion.h
    ${CMAKE_SOURCE_DIR}/Extrusion/src/Extrusion.cpp
    ${CMAKE_SOURCE_DIR}/Extrusion/include/Structure.h
    ${CMAKE_SOURCE_DIR}/Extrusion/src/Structure.cpp
    ${CMAKE_SOURCE_DIR}/Extrusion/include/extrusionWindow.h
    ${CMAKE_SOURCE_DIR}/Extrusion/src/extrusionWindow.cpp
    ${CMAKE_SOURCE_DIR}/Extrusion/include/ExtWidget.h
    ${CMAKE_SOURCE_DIR}/Extrusion/src/ExtWidget.cpp
    ${CMAKE_SOURCE_DIR}/Bezier/include/Bezier.h
    ${CMAKE_SOURCE_DIR}/Bezier/src/Bezier.cpp
    ${CMAKE_SOURCE_DIR}/Bezier/include/BezierWidget.h
    ${CMAKE_SOURCE_DIR}/Bezier/src/BezierWidget.cpp
    ${CMAKE_SOURCE_DIR}/Bezier/include/bezierWindow.h
    ${CMAKE_SOURCE_DIR}/Bezier/src/bezierWindow.cpp
)

# Set Qt installation path
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64")

# Find required Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add the geometry shared library
add_library(geometry SHARED ${GEOMETRY_SRC})

# Link Qt and OpenGL libraries to the geometry library
target_link_libraries(geometry
    Qt6::OpenGL
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    OpenGL::GL
)

# Add the main application executable
add_executable(GeometryApp ${APPLICATION_SRC})

# Link geometry and other libraries to the main application
target_link_libraries(GeometryApp
    geometry
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    GLU32
    OpenGL32
)

# Add a custom target to clean .dat, .stl, and .obj files from the scripts directory
add_custom_target(clean_scripts
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning .dat, .stl, and .obj files from scripts directory..."
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/geometry/scripts
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/geometry/scripts
    COMMENT "Cleaning up generated files in scripts directory"
)

# Ensure the clean_scripts target runs before the build
add_dependencies(GeometryApp clean_scripts)