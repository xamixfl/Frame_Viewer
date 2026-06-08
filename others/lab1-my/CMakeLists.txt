cmake_minimum_required(VERSION 3.16)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("OOP_Lab1_FrameViewer")

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
	"src"
	"src/common"
	"src/gui"
	"src/task_manager"
	"src/projection"
	"src/drawer"
	"src/model"
)

add_executable(OOP_Lab1_FrameViewer
	WIN32
	"src/main.cpp"
	"src/common/common_types.h"
	"src/gui/mainwindow.cpp" "src/gui/mainwindow.h" "src/gui/mainwindow.ui"
	"src/gui/viewerwidget.cpp" "src/gui/viewerwidget.h"
	"src/task_manager/task_manager.c" "src/task_manager/task_manager.h"
	"src/projection/projection.c" "src/projection/projection.h"
	"src/drawer/drawer.cpp" "src/drawer/drawer.h"
	"src/common/obj_format.h"
	"src/model/model.c" "src/model/model.h"
	"src/model/edge.c" "src/model/edge.h"
	"src/model/point.c" "src/model/point.h"
	"src/common/getline.c" "src/common/getline.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET OOP_Lab1_FrameViewer PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(OOP_Lab1_FrameViewer PRIVATE Qt6::Widgets)
