cmake_minimum_required(VERSION 3.0)

project(WolfEngine VERSION 0.1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_CXX_STANDARD 17)

set(WOLF_ENGINE_RELATIVE_TO_ROOT_PATH ".")
add_subdirectory(Wolf)
add_subdirectory(Sandbox)

add_library(engine_library INTERFACE)

target_link_libraries(engine_library INTERFACE engine_lib)
target_link_libraries(engine_library INTERFACE lib_sandbox)

# Creates executable
add_executable(${PROJECT_NAME} main.cpp)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)


# Links the libraries to the executable
target_link_libraries(${PROJECT_NAME} engine_library)

