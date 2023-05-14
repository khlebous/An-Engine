project(TestsAnEngine)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Adding library with the above source.
add_executable(
    ${PROJECT_NAME}
        ${SOURCES}
)


add_library(AnEngine2
        ${CMAKE_SOURCE_DIR}/Source/AnEngine/include/AnEngine/LayerStack.h
        ${CMAKE_SOURCE_DIR}/Source/AnEngine/src/LayerStack.cpp
)

target_link_libraries(AnEngine2)


target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/Source/AnEngine/include
)




#redirectOutputPath(${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME})