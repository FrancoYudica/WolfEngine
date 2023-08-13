
message("VENDOR-CMAKE Loading vendor libraries")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(imgui)


# Loads stb target as static library
file(GLOB STB_FILES stb/*.h stb/*.c)
add_library(stb_lib STATIC ${STB_FILES})
set_target_properties(stb_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(vendor_lib INTERFACE)
target_include_directories(vendor_lib INTERFACE "./stb")
target_link_libraries(vendor_lib INTERFACE glfw)
target_link_libraries(vendor_lib INTERFACE glm)
target_link_libraries(vendor_lib INTERFACE glad)
target_link_libraries(vendor_lib INTERFACE imgui)
target_link_libraries(vendor_lib INTERFACE stb_lib)
