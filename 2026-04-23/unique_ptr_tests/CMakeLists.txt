# Necessary
cmake_minimum_required(VERSION 3.22.1)

# Project Name
project(
    unique-ptr-tests
    LANGUAGES CXX    
)

add_executable(
    ${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/main.cpp"
    "${PROJECT_SOURCE_DIR}/payload_ptr.cpp"
    "${PROJECT_SOURCE_DIR}/payload_array.cpp"
    "${PROJECT_SOURCE_DIR}/payload_vector.cpp"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/./"
)

