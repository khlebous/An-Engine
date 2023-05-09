cmake_minimum_required (VERSION 3.8)

project(glad)

set(HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/include/glad/glad.h"
    "${CMAKE_CURRENT_LIST_DIR}/include/KHR/khrplatform.h"
)

set(SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/glad.c"
)

add_library(
    ${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

