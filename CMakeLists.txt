cmake_minimum_required(VERSION 3.15)

project(ble-heart-rate-demo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ROOT_PROJECT_DIR ${CMAKE_SOURCE_DIR} CACHE INTERNAL "Root project directory")

if (MSVC)
    add_compile_options(
      /W4
      /bigobj
    )
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (MINGW)
    add_compile_options(-Wa,-mbig-obj)
endif()

option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if(ENABLE_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-O0 -coverage -fprofile-arcs -fprofile-instr-generate -fcoverage-mapping)
        add_link_options(-O0 -coverage -fprofile-arcs -fprofile-instr-generate -fcoverage-mapping)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(-O0 -coverage)
        add_link_options(-O0 -coverage)
    endif()
endif()

if(ENABLE_STATIC_ANALYSIS)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if(CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK
                "--enable=all"
                "--library=qt"
        )
    endif()
endif()

include(CTest)
enable_testing()

add_subdirectory(app)
add_subdirectory(libs)
add_subdirectory(test)
#add_executable(new_target app/main.cpp)
