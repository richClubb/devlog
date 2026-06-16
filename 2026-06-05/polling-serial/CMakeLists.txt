cmake_minimum_required(VERSION 3.25)

project(polling_serial LANGUAGES C)

add_executable(
    "${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/main.c"
)

target_include_directories(
    "${PROJECT_NAME}"
    PRIVATE
    "${PROJECT_SOURCE_DIR}/"
)