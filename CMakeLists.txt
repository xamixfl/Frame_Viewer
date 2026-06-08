cmake_minimum_required(VERSION 3.16)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("OOP_Lab3_FrameViewer")

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(assimp CONFIG REQUIRED)

include_directories(
	"src"
)

set(DOMAIN_SOURCES
    src/data/Point.cpp

    src/bridge/VectorCompositeImpl.cpp
    src/bridge/CarcasCamera.cpp

    src/memento/Memento.cpp

    src/reader/FileReader.cpp
    src/reader/BinaryReader.cpp
    src/reader/AutoReader.cpp

    src/composite/BaseObject.cpp
    src/composite/CompositeObject.cpp
    src/composite/Scene.cpp
    src/composite/Model.cpp
    src/composite/Camera.cpp

    src/visitor/MoveVisitor.cpp
    src/visitor/RotateVisitor.cpp
    src/visitor/ScaleVisitor.cpp
    src/visitor/DrawVisitor.cpp

    src/builder/BaseBuilder.cpp
    src/builder/CarcasModelBuilder.cpp
    src/builder/CarcasCameraBuilder.cpp
    src/builder/SceneBuilder.cpp

    src/director/CarcasModelDirector.cpp
    src/director/CarcasCameraDirector.cpp
    src/director/SceneDirector.cpp

    src/solution/Solution.cpp

    src/manager/LoadManager.cpp
    src/manager/SceneManager.cpp
    src/manager/TransformManager.cpp
    src/manager/DrawManager.cpp
    src/manager/HistoryManager.cpp

    src/facade/Facade.cpp

    src/command/ModelCommands.cpp
    src/command/CameraCommands.cpp
    src/command/SceneCommands.cpp
    src/command/TransformCommands.cpp
    src/command/HistoryCommands.cpp

    src/factory/QtDrawer.cpp
    src/factory/QtDrawerFactory.cpp

    src/bridge/AssimpModelImpl.cpp
    src/builder/AssimpModelBuilder.cpp
    src/director/AssimpDirector.cpp
    src/bridge/AssimpModelImpl.cpp
    src/director/AssimpDirector.cpp  
    src/reader/AssimpReader.cpp
    src/builder/AssimpModelBuilder.cpp
    src/director/AssimpDirector.cpp
    src/composite/Light.cpp     
    src/bridge/LightImpl.cpp
)

set(UI_SOURCES
    src/ui/MainWindow.cpp
)

add_executable(OOP_Lab3_FrameViewer
	"src/main.cpp"
	${DOMAIN_SOURCES}
	${UI_SOURCES}
)

target_link_libraries(OOP_Lab3_FrameViewer PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    assimp::assimp
)
