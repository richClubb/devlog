cmake_minimum_required(VERSION 3.10)

project(
    cpp_int_math
    LANGUAGES C
)

add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/main.cpp")

set(PATH "${PROJECT_SOURCE_DIR}")
message("${PATH}")

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/../cpp_lib/include 
    ${PROJECT_SOURCE_DIR}/../../c/c_lib/include
)

target_link_directories(
    ${PROJECT_NAME}
    PUBLIC 
    "${PROJECT_SOURCE_DIR}/../cpp_lib/lib" 
    "${PROJECT_SOURCE_DIR}/../../c/c_lib/lib"
)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
    "cpp_int_math_lib"
    "c_int_math_lib"
    )