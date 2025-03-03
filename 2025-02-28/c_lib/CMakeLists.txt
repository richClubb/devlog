# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_STANDARD 12)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")

cmake_minimum_required(VERSION 3.25)

project(
    c_add
    LANGUAGES C
)

add_library(c_add src/c_add.c)

target_include_directories(c_add PRIVATE include)

