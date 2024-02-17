cmake_minimum_required(VERSION 3.27)
project(ImguiD3Cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/outpus)

FILE(GLOB_RECURSE FILE_INCLUDES include/*.h*)
include_directories(
        include/imgui
        include/Hack
)

FILE(GLOB_RECURSE FILE_SOURCE src/*.c*)

add_executable(ImguiD3Cmake
        ${FILE_INCLUDES}
        ${FILE_SOURCE}
        src/application.cpp
)
target_link_directories(
        ImguiD3Cmake
        PRIVATE
        WIN32
)