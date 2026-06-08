cmake_minimum_required(VERSION 3.5)

project(code VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_MIN_VERSION 6.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "QT_VERSION_MAJOR = ${QT_VERSION_MAJOR}")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    mainwindow.cpp
    Exception.h
    mainwindow.h
    main.cpp
    visitor/AbstractVisitor.h
    visitor/AbstractVisitor.cpp
    loader/AbstractReader.cpp
    loader/Loader.cpp
    loader/BinaryReader.cpp
    loader/FileReader.cpp
    loader/AbstractReader.h
    loader/FileReader.h
    loader/Loader.h
    loader/BinaryReader.h
    object/Model.h
    object/AbstractObject.cpp
    object/Model.cpp
    object/AbstractObject.h
    object/carcas/MatrixCarcas.h
    object/carcas/MatrixCarcas.cpp
    object/carcas/TriangleCarcas.h
    object/carcas/TriangleCarcas.cpp
    object/carcas/AbstractCarcas.h
    object/carcas/Carcas.h
    object/carcas/Carcas.cpp
    object/camera/Camera.cpp
    object/camera/Camera.h
    modelvisitor/RotateVisitor.cpp
    modelvisitor/ModelVisitor.h
    modelvisitor/ScaleVisitor.h
    modelvisitor/ScaleVisitor.cpp
    modelvisitor/MoveVisitor.cpp
    modelvisitor/RotateVisitor.h
    modelvisitor/MoveVisitor.h
    solution/SolutionScene.cpp
    solution/SolutionDraw.cpp
    solution/SolutionDraw.h
    solution/SolutionTransform.h
    solution/SolutionTransform.cpp
    solution/BaseSolution.h
    solution/SolutionLoader.cpp
    solution/BaseSolution.cpp
    solution/SolutionScene.h
    solution/SolutionLoader.h
    command/BaseCommand.h
    command/CameraCommand.h
    command/BaseCommand.cpp
    command/DrawCommand.cpp
    command/ModelCommand.h
    command/ModelCommand.cpp
    command/CameraCommand.cpp
    command/SceneCommand.h
    command/DrawCommand.h
    command/SceneCommand.cpp
    scene/Scene.cpp
    scene/Scene.h
    facade/Facade.cpp
    facade/Facade.h
    builder/BaseDirector.cpp
    builder/CarcasBuilder.h
    builder/MatrixBuilder.cpp
    builder/TriangleBuilder.h
    builder/TriangleBuilder.cpp
    builder/CarcasBuilder.cpp
    builder/CarcasDirector.cpp
    builder/CarcasDirector.h
    builder/DirectorCreator.cpp
    builder/BaseDirector.h
    builder/MatrixBuilder.h
    builder/BaseCarcasBuilder.h
    builder/DirectorCreator.h
    draw/QtFactory.h
    draw/AbstractDrawer.h
    draw/DrawAll.cpp
    draw/DrawVisitor.cpp
    draw/AbstractDrawer.cpp
    draw/QtFactory.cpp
    draw/QtDrawer.h
    draw/DrawAll.h
    draw/DrawVisitor.h
    draw/AbstractGraphicFactory.h
    draw/QtDrawer.cpp
    draw/AbstractGraphicFactory.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(code
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET code APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(code SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(code
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(code PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# target_link_directories(code PRIVATE eigen)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.code)
endif()
set_target_properties(code PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS code
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(code)
endif()
