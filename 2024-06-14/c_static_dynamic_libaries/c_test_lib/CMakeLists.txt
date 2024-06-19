# Necessary
cmake_minimum_required(VERSION 3.22.1)

# Project Name
project(add-lib)

# Include directory There is also target_include_directory which applies to specific libs
# include_directories(includes)
add_library(add-lib SHARED src/add_lib.c)
target_include_directories(add-lib PRIVATE includes)
set(CMAKE_C_STANDARD 23)


add_executable(add-lib-dyn main.c)
target_include_directories(add-lib-dyn PRIVATE includes)
target_link_libraries(add-lib-dyn add-lib)
#set_property(add-lib-dyn tgt PROPERTY C_STANDARD 23)
