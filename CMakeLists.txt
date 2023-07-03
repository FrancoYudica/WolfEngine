cmake_minimum_required(VERSION 3.0)
project(WolfEngineProject)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Wolf/vendor)
add_subdirectory(Wolf/Wolf)
add_subdirectory(Wolf/Platform)

# Creates the wolf_engine_library
add_library(engine_lib INTERFACE)

# Adds all it's dependecies
target_link_libraries(engine_lib INTERFACE vendor_lib)
target_link_libraries(engine_lib INTERFACE wolf_engine_lib)
target_link_libraries(engine_lib INTERFACE platform_lib)

option(WOLF_BUILD_TESTS "Builds the WOLF example programs")

if (WOLF_BUILD_TESTS)
    add_subdirectory(Wolf/tests)
endif()