cmake_minimum_required (VERSION 3.15)

project ("AnEngine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory (Source)

add_subdirectory (external/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory (external/glad)
add_subdirectory (external/imgui)

    enable_testing()
    add_subdirectory(tests)
