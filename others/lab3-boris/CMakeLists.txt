cmake_minimum_required(VERSION 3.16)
project(OOP_LAB_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB_RECURSE SOURCES "*.cpp")

list(FILTER SOURCES EXCLUDE REGEX ".*/build/.*")
list(FILTER SOURCES EXCLUDE REGEX ".*/CMakeFiles/.*")

file(GLOB_RECURSE UI_FILES "*.ui")

add_executable(oop_lab_03 ${SOURCES} ${UI_FILES})

target_compile_options(oop_lab_03 PRIVATE
    -Wall -Werror -Wextra -Wpedantic
)

target_compile_options(oop_lab_03 PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wno-unused-parameter>
)

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "*")
foreach(DIR ${INCLUDE_DIRS})
    if(IS_DIRECTORY "${DIR}")
        target_include_directories(oop_lab_03 PRIVATE "${DIR}")
    endif()
endforeach()

target_link_libraries(oop_lab_03 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
