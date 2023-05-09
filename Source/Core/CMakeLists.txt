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

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
)
