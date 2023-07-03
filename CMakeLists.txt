cmake_minimum_required(VERSION 3.0)
project(WolfEngineProject)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Wolf/vendor)
add_subdirectory(Wolf/Wolf)
add_subdirectory(Wolf/Platform)

# Creates the wolf_engine_library
add_library(wolf_engine INTERFACE)

# Adds all it's dependecies
target_link_libraries(wolf_engine INTERFACE vendor_lib)
target_link_libraries(wolf_engine INTERFACE engine_lib)
target_link_libraries(wolf_engine INTERFACE platform_lib)

option(WOLF_BUILD_TESTS "Builds WOLF example programs" OFF)

if (WOLF_BUILD_TESTS)
    add_subdirectory(Wolf/tests)
endif()