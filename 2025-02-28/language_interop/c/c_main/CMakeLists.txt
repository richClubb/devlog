cmake_minimum_required(VERSION 3.10)

project(
    c_int_math
    LANGUAGES C
)

add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/main.c")

set(PATH "${PROJECT_SOURCE_DIR}")
message("${PATH}")

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/../c_lib/include 
    ${PROJECT_SOURCE_DIR}/../../cpp/cpp_lib/include
)

target_link_directories(
    ${PROJECT_NAME}
    PUBLIC 
    "${PROJECT_SOURCE_DIR}/../c_lib/lib" 
    "${PROJECT_SOURCE_DIR}/../../cpp/cpp_lib/lib"
)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
    "c_int_math_lib"
    "cpp_int_math_lib"
    )