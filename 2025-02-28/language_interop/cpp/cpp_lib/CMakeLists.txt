# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_STANDARD 12)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")

cmake_minimum_required(VERSION 3.25)

project(
    cpp_int_math_lib
    LANGUAGES CXX
)

add_library("${PROJECT_NAME}_lib" "src/cpp_int_math.cpp")

target_include_directories("${PROJECT_NAME}_lib" PRIVATE "include")

# For Unit Tests
add_executable(
    "${PROJECT_NAME}_unit_tests" 
    "${PROJECT_SOURCE_DIR}/tests/unit/test_cpp_int_math_lib.cpp"
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
    "cpp_int_math_lib"
    "cunit"
)