message("Adding WolfEngine")

file(GLOB WOLF_CORE_H            core/*.h)
file(GLOB WOLF_CORE_CPP          core/*.cpp)

file(GLOB WOLF_IMGUI_LAYER_H     imgui_layer/*.h)
file(GLOB WOLF_IMGUI_LAYER_CPP   imgui_layer/*.cpp)

file(GLOB WOLF_RENDERING_H       rendering/*.h rendering/batch/*.h)
file(GLOB WOLF_RENDERING_CPP     rendering/*.cpp rendering/batch/*.cpp)

file(GLOB WOLF_NUMERICAL_H       numerical/*.h)
file(GLOB WOLF_NUMERICAL_CPP     numerical/*.cpp)

file(GLOB WOLF_UTILS_H           utils/*.h)
file(GLOB WOLF_UTILS_CPP         utils/*.cpp)

file(GLOB WOLF_INPUT_H           input/*.h)
file(GLOB WOLF_INPUT_CPP         input/*.cpp)

file(GLOB WOLF_ASSETS_H           assets/*.h)
file(GLOB WOLF_ASSETS_CPP         assets/*.cpp)

file(GLOB WOLF_ANIMATION_H           animation/*.h)
file(GLOB WOLF_ANIMATION_CPP         animation/*.cpp)


add_library(
    engine_lib STATIC
    WEngine.h
    ${WOLF_CORE_H}
    ${WOLF_CORE_CPP}
    ${WOLF_IMGUI_LAYER_H}
    ${WOLF_IMGUI_LAYER_CPP}
    ${WOLF_RENDERING_H}
    ${WOLF_RENDERING_CPP}
    ${WOLF_NUMERICAL_H}
    ${WOLF_NUMERICAL_CPP}
    ${WOLF_UTILS_H}
    ${WOLF_UTILS_CPP}
    ${WOLF_INPUT_H}
    ${WOLF_INPUT_CPP}
    ${WOLF_ASSETS_H}
    ${WOLF_ASSETS_CPP}
    ${WOLF_ANIMATION_H}
    ${WOLF_ANIMATION_CPP}
    )

target_link_libraries(engine_lib PRIVATE vendor_lib)

# Need to link with plaform, because the Rendering definitions are there
target_link_libraries(engine_lib PRIVATE platform_lib)

target_include_directories(
    engine_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(engine_lib INTERFACE WOLF_ENGINE_VERSION=0.1)

# WOLF ENGINE REQUIERES WOLF_ENGINE_RELATIVE_TO_ROOT_PATH to be set by the user
target_compile_definitions(engine_lib PUBLIC WOLF_ENGINE_PATH="${WOLF_ENGINE_RELATIVE_TO_ROOT_PATH}")


if (WOLF_DEBUG)
    target_compile_definitions(engine_lib PUBLIC WOLF_DEBUG_MODE)
endif()