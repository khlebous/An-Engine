cmake_minimum_required (VERSION 3.8)

project(Core)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR} "*.h")
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR} "*.cpp")

add_library(
    ${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/spdlog/include
)

add_library(an::Core ALIAS ${PROJECT_NAME})

target_compile_definitions(
    ${PROJECT_NAME} 
        PRIVATE GLFW_INCLUDE_NONE=1
        PRIVATE AN_ENABLE_ASSERTS=1
        PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

configure_file(
    "${CMAKE_SOURCE_DIR}/config/config.txt"
    "${CMAKE_BINARY_DIR}/config/config.h"
)
