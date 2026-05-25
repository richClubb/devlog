cmake_minimum_required(VERSION 3.18)

project(
    libsodium_example
    LANGUAGES C
)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.c
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/.
)

target_link_libraries(
    ${PROJECT_NAME}
    sodium
)