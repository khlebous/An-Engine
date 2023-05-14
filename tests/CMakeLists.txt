set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

# -------------------------------------------------------------------------------------------------
# Configure build of googletest
# -------------------------------------------------------------------------------------------------
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_GetProperties(gtest)
if(NOT gtest_POPULATED)
  FetchContent_Populate(gtest)
  add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR})
  
   set_target_properties(
            gtest PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Deployment/${CMAKE_BUILD_TYPE}/AAA/arch"
                LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Deployment/${CMAKE_BUILD_TYPE}/AAA/lib"
                RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Deployment/${CMAKE_BUILD_TYPE}/AAA/bin"
            )

endif()

include(GoogleTest)

# -------------------------------------------------------------------------------------------------
# Add GTest
# -------------------------------------------------------------------------------------------------

add_subdirectory(TestsAnEngine)
