
add_subdirectory(Opengl)
add_library(platform INTERFACE)
target_link_libraries(platform INTERFACE opengl_impl)