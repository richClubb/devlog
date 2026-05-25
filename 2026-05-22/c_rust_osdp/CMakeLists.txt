cmake_minimum_required(VERSION 3.25)

project(c_rust_osdp_example LANGUAGES C)

add_executable(
    ${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/main.c"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/../rust_osdp/"
)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/../rust_osdp/target/release/"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    rust_osdp
)