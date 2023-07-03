cmake_minimum_required(VERSION 3.0)

set(TEST_EXECUTABLE_NAME TestWolf)

project(${TEST_EXECUTABLE_NAME})

add_executable(${TEST_EXECUTABLE_NAME} test.cpp batch_renderer_test.hpp batch_renderer_test.cpp)

target_link_libraries(${TEST_EXECUTABLE_NAME} wolf_engine)

# Outputs the test executable in the build folder
set_target_properties(${TEST_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)