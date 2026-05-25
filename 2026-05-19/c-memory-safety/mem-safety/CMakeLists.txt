cmake_minimum_required(VERSION 3.18)

project(
    mem_safety
    LANGUAGES C
)

add_library(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/mem_safety.c
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/.
)