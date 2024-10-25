cmake_minimum_required(VERSION 3.5)
project(im CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(test)
