cmake_minimum_required (VERSION 3.8)

project(imgui)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR} "*.cpp")
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR} "*.h")

add_library(
    ${PROJECT_NAME}
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3.h
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/imgui
)
