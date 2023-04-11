
message("Adding Platform-Opengl")

file(GLOB WOLF_OPENGL_IMPL_CPP "*.cpp")
file(GLOB WOLF_OPENGL_IMPL_H ".h")

add_library(
    opengl_impl STATIC
    ${WOLF_OPENGL_IMPL_H}
    ${WOLF_OPENGL_IMPL_CPP}
)

target_link_libraries(opengl_impl PRIVATE vendor)
target_link_libraries(opengl_impl PRIVATE wolf_engine)
