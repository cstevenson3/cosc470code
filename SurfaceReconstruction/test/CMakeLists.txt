# Configuring Catch.
set(CATCH_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable.
include_directories(${CMAKE_HOME_DIRECTORY}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/testresources)
set(TEST_SOURCES TestMain.cpp
        ContourTests.cpp
        TriangulationTests.cpp
        DTWPerformance.cpp
        ContoursPerformance.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch lib_surface_reconstruction)