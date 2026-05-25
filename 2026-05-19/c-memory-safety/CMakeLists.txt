cmake_minimum_required(VERSION 3.18)

project(
    mem_safety_main
    LANGUAGES C
)

add_subdirectory(${PROJECT_SOURCE_DIR}/mem-safety/)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.c
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/.
    ${PROJECT_SOURCE_DIR}/mem-safety/
)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/mem-safety/build/
)

target_link_libraries(
    ${PROJECT_NAME}
    mem_safety
)