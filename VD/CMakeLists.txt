cmake_minimum_required(VERSION 3.14)

project(VoronoiApp)

set(CMAKE_CXX_STANDARD 17)

# Add Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Boost
find_package(Boost REQUIRED)
find_package(Boost REQUIRED CONFIG)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("C:/Users/Anjali Dongare/vcpkg/installed/x64-windows/include")



include_directories(
    ${Boost_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    main.cpp
    Voronoi.cpp
    VoronoiWidget.cpp
    mainwindow.cpp
)

set(HEADERS
    Voronoi.h
    VoronoiWidget.h
    mainwindow.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
)
