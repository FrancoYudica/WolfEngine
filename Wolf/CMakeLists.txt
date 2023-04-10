
set(WOLF_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Wolf)
add_subdirectory(Platform)
add_subdirectory(Sandbox)


# Creates the wolf_engine_library
add_library(wolf_engine_library INTERFACE)

# Adds all it's dependecies
target_link_libraries(wolf_engine_library INTERFACE vendor)
target_link_libraries(wolf_engine_library INTERFACE wolf_engine)
target_link_libraries(wolf_engine_library INTERFACE platform)
target_link_libraries(wolf_engine_library INTERFACE lib_sandbox)

# Creates executable
add_executable(${PROJECT_NAME} main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Links the libraries to the executable
target_link_libraries(${PROJECT_NAME} wolf_engine_library)
#target_link_libraries(${PROJECT_NAME} lib_sandbox)