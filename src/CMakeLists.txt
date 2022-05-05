add_library(probt3c_impl
    basic_vectors.cc
)
add_executable(probt3c_exec probt3c.cc)
target_link_libraries(probt3c_exec probt3c_impl)
set_target_properties(probt3c_exec
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
install(TARGETS probt3c_exec)
