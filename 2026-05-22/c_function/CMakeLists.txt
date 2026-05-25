cmake_minimum_required(VERSION 3.25)

project(a_lib_main LANGUAGES C)

add_subdirectory("${PROJECT_SOURCE_DIR}/a_lib")

add_executable(
    ${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/main.c"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/a_lib/"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    a_lib
)