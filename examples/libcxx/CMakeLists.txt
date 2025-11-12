cmake_minimum_required(VERSION 3.22)
project(example_driver LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../") # examples/../FindCrossWDK.cmake
find_package(CrossWDK REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

wdk_add_driver(example_driver
        main.cpp
)

target_compile_options(example_driver PRIVATE
        -g3
)
