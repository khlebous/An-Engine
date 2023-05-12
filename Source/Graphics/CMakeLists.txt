cmake_minimum_required (VERSION 3.8)

project(Graphics)

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
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${CMAKE_SOURCE_DIR}/external/spdlog/include
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE 
        external/glad/src
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC 
        an::Core
        glad
)

add_library(an::Graphics ALIAS ${PROJECT_NAME})

target_compile_definitions(
    ${PROJECT_NAME} 
        PRIVATE AN_ENABLE_ASSERTS=1
        PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
