cmake_minimum_required(VERSION 3.25)

project(epoll_uart LANGUAGES C)

add_executable(
    "${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/main.c"
    "${PROJECT_SOURCE_DIR}/async_serial.c"
)

target_include_directories(
    "${PROJECT_NAME}"
    PRIVATE
    "${PROJECT_SOURCE_DIR}/"
)