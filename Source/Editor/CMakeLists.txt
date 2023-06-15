cmake_minimum_required (VERSION 3.15)

project(Editor)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR} "*.h")
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR} "*.cpp")

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_BINARY_DIR}/config
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/Source/Engine/include
        ${CMAKE_SOURCE_DIR}/external/imgui/
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE 
        external/glfw/src
        external/imgui/
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC 
        an::Engine
)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/resources")
file(COPY "${CMAKE_SOURCE_DIR}/resources/" DESTINATION "${CMAKE_BINARY_DIR}/resources")
