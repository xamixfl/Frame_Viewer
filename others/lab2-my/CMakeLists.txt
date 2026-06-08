cmake_minimum_required(VERSION 3.16)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("OOP_Lab2_VectorClass")

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
	"src"
	"src/Vector"
	"src/Iterator"
	"src/Exception"
)

add_executable(OOP_Lab2_VectorClass
	"src/main.cpp"
	"src/Vector/BaseVector.cpp"
	"src/Iterator/BaseIterator.cpp"
)
