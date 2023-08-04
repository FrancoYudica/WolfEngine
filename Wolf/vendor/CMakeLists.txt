
message("VENDOR-CMAKE Loading vendor libraries")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(imgui)


# Loads stb target as static library
file(GLOB STB_HEADERS ./stb/*.h)
add_library(stb STATIC ${STB_HEADERS})
set_target_properties(stb PROPERTIES LINKER_LANGUAGE CXX)

add_library(vendor_lib INTERFACE)

target_link_libraries(vendor_lib INTERFACE glfw)
target_link_libraries(vendor_lib INTERFACE glm)
target_link_libraries(vendor_lib INTERFACE glad)
target_link_libraries(vendor_lib INTERFACE imgui)
target_link_libraries(vendor_lib INTERFACE stb)
