cmake_minimum_required(VERSION 3.25)

project(a_lib LANGUAGES C)

add_library(
    ${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/a_lib.c"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/./"
)