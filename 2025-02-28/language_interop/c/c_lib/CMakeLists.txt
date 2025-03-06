# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_STANDARD 12)

cmake_minimum_required(VERSION 3.25)

project(
    c_int_math
    LANGUAGES C
)

# For Library Creation
add_library(
    "${PROJECT_NAME}_lib" 
    "${PROJECT_SOURCE_DIR}/src/c_int_math.c"
)

target_include_directories(
    "${PROJECT_NAME}_lib" 
    PRIVATE 
    "${PROJECT_SOURCE_DIR}/include"
)

add_custom_command(
    TARGET 
    "${PROJECT_NAME}_lib" 
    POST_BUILD
    COMMAND 
    ${CMAKE_COMMAND} -E copy libc_int_math_lib.a ${PROJECT_SOURCE_DIR}/lib/
)

# For Unit Tests
add_executable(
    "${PROJECT_NAME}_unit_tests" 
    "${PROJECT_SOURCE_DIR}/tests/unit/test_c_int_math_lib.c"
)

target_include_directories(
    "${PROJECT_NAME}_unit_tests" 
    PRIVATE 
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_directories(
    "${PROJECT_NAME}_unit_tests" 
    PUBLIC 
    "${PROJECT_SOURCE_DIR}/lib"
    "/usr/lib/x86_64-linux-gnu/"
)

target_link_libraries(
    "${PROJECT_NAME}_unit_tests" 
    PUBLIC
    "c_int_math_lib"
    "cunit"
)

