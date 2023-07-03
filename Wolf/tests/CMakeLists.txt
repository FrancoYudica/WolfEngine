cmake_minimum_required(VERSION 3.0)
project(WolfTest)

add_executable(WolfTest test.cpp batch_renderer_test.hpp batch_renderer_test.cpp)

target_link_libraries(WolfTest engine_lib)

# Outputs the test executable in the build folder
set_target_properties(WolfTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)