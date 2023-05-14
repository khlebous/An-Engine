project(TestsAnEngine)

enable_testing()
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

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(
    AnEngine2
    gtest gtest_main)


target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/Source/AnEngine/include
)


#gtest_discover_tests(${PROJECT_NAME})