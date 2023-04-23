file(GLOB WOLF_SANDBOX_H *.h)
file(GLOB WOLF_SANDBOX_CPP *.cpp)

include_directories(./Wolf/Wolf)

add_library(lib_sandbox STATIC
    ${WOLF_SANDBOX_H}
    ${WOLF_SANDBOX_CPP}
)

# Links the whole engine_library to the sandbox files
target_link_libraries(lib_sandbox PRIVATE engine_library)
