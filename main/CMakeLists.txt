cmake_minimum_required(VERSION 3.10)

Project( CPU_USAGE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_library(compiler_flags INTERFACE)
set(C_FLAGS)
list(APPEND C_FLAGS "-pthread" "-Wall" "-Wextra" "-std=c++11" "-g" )
target_compile_options(compiler_flags INTERFACE ${C_FLAGS})

add_subdirectory(src)

add_executable(CPU_USAGE main.cpp)

target_link_libraries(CPU_USAGE PUBLIC Function compiler_flags)

 