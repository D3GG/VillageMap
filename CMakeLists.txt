cmake_minimum_required(VERSION 3.16)

project(VillageMap
    VERSION 0.1.0
    DESCRIPTION "CLI tourism guide for small settlements in Bulgaria"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(VillageMap ${SOURCES}
        src/Landmark.cpp
        src/Landmark.h)

target_include_directories(VillageMap PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

if(MSVC)
    target_compile_options(VillageMap PRIVATE /W4 /permissive-)
else()
    target_compile_options(VillageMap PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE FORMAT_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${FORMAT_FILES}
        COMMENT "Formatting source files with clang-format"
    )
endif()