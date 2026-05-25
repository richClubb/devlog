cmake_minimum_required(VERSION 3.25)

project(c_main_calling_rust LANGUAGES C)

add_executable(
    ${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/main.c"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/../rust_lib_callback_example/"
)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/../rust_lib_callback_example/target/release/"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    rust_lib_callback_example
)