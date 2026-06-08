cmake_minimum_required(VERSION 3.5)
project(lab_03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/qt_ui/)

file(GLOB_RECURSE SOURCES
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.hpp"
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.ui"
        "${PROJECT_SOURCE_DIR}/*.qrc"
)

# Exclude CMake generated files and build directories
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}")
list(FILTER SOURCES EXCLUDE REGEX "CMakeFiles")
list(FILTER SOURCES EXCLUDE REGEX "cmake-build-")
list(FILTER SOURCES EXCLUDE REGEX "_autogen")

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(lab_03 ${SOURCES})

target_include_directories(lab_03 PRIVATE
        ${PROJECT_ROOT_DIR}
        ${PROJECT_ROOT_DIR}/Command
        ${PROJECT_ROOT_DIR}/Command/Camera
        ${PROJECT_ROOT_DIR}/Command/Scene
        ${PROJECT_ROOT_DIR}/Command/Model
        ${PROJECT_ROOT_DIR}/Command/History
        ${PROJECT_ROOT_DIR}/Facade
        ${PROJECT_ROOT_DIR}/Managers
        ${PROJECT_ROOT_DIR}/Managers/Creator
        ${PROJECT_ROOT_DIR}/Managers/ManagerSolution
        ${PROJECT_ROOT_DIR}/Managers/LoadManager
        ${PROJECT_ROOT_DIR}/Managers/DrawManager
        ${PROJECT_ROOT_DIR}/Managers/SceneManager
        ${PROJECT_ROOT_DIR}/Managers/CameraManager
        ${PROJECT_ROOT_DIR}/Managers/TransformManager
        ${PROJECT_ROOT_DIR}/Managers/HistoryManager
        ${PROJECT_ROOT_DIR}/Objects
        ${PROJECT_ROOT_DIR}/Objects/Composite
        ${PROJECT_ROOT_DIR}/Objects/InvisibleObjects
        ${PROJECT_ROOT_DIR}/Objects/InvisibleObjects/Cameras
        ${PROJECT_ROOT_DIR}/Objects/VisibleObjects
        ${PROJECT_ROOT_DIR}/Objects/VisibleObjects/Models
        ${PROJECT_ROOT_DIR}/Objects/VisibleObjects/Models/CarcassModel
        ${PROJECT_ROOT_DIR}/Primitives
        ${PROJECT_ROOT_DIR}/Concepts
        ${PROJECT_ROOT_DIR}/Visitors/
        ${PROJECT_ROOT_DIR}/Visitors/DrawVisitor
        ${PROJECT_ROOT_DIR}/Visitors/TransformVisitors
        ${PROJECT_ROOT_DIR}/Drawer
        ${PROJECT_ROOT_DIR}/Drawer/QtDrawer
        ${PROJECT_ROOT_DIR}/Builders
        ${PROJECT_ROOT_DIR}/Builders/ModelDirectors
        ${PROJECT_ROOT_DIR}/Builders/ModelBuilders
        ${PROJECT_ROOT_DIR}/Scene
        ${PROJECT_ROOT_DIR}/Exceptions
        ${PROJECT_ROOT_DIR}/Transformations
        ${PROJECT_ROOT_DIR}/Reader
        ${PROJECT_ROOT_DIR}/rapidcsv
        ${PROJECT_ROOT_DIR}/CareTaker
        ${PROJECT_ROOT_DIR}/qt_ui
)

target_link_libraries(lab_03
        Qt::Core
        Qt::Gui
        Qt::Widgets
)