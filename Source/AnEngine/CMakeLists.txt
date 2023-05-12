cmake_minimum_required (VERSION 3.15)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR} "*.h")
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR} "*.cpp")

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/
        ${CMAKE_SOURCE_DIR}/external/imgui/
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${CMAKE_SOURCE_DIR}/external/glfw/include
)


target_link_directories(
    ${PROJECT_NAME} PRIVATE 
        external/glad/src
        external/glfw/src
        external/imgui/
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC 
        an::Core
        an::Graphics
        glad
        glfw
        opengl32
        imgui
)

target_compile_definitions(
    ${PROJECT_NAME} 
        PRIVATE GLFW_INCLUDE_NONE=1
        PRIVATE AN_ENABLE_ASSERTS=1
        PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
