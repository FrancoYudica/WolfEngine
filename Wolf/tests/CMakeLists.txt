cmake_minimum_required(VERSION 3.0)

set(TEST_EXECUTABLE_NAME TestWolf)

project(${TEST_EXECUTABLE_NAME})

file(
    GLOB TEST_FILES
    renderer/*.cpp renderer/*.h renderer/*.hpp
    imgui_tests/*.cpp imgui_tests/*.hpp
    *.cpp *.h *.hpp
)

add_executable(${TEST_EXECUTABLE_NAME} test.cpp ${TEST_FILES})

target_link_libraries(${TEST_EXECUTABLE_NAME} wolf_engine)

# Outputs the test executable in the build folder
set_target_properties(${TEST_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)