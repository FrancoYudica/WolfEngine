
message("Adding Platform-Opengl")

file(GLOB WOLF_OPENGL_IMPL_CPP "*.cpp")
file(GLOB WOLF_OPENGL_IMPL_H "*.h" "*.tcc")

add_library(
    opengl_lib STATIC
    ${WOLF_OPENGL_IMPL_H}
    ${WOLF_OPENGL_IMPL_CPP}
)

target_link_libraries(opengl_lib PRIVATE vendor_lib)
target_link_libraries(opengl_lib PRIVATE engine_lib)
