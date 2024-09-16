cmake_minimum_required(VERSION 3.5)

project(container_benchmarks)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(benchmarks PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(src)
