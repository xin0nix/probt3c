# Compile as a static lib and link
add_library(BasicArrays STATIC BasicArrays.cpp)
target_include_directories(BasicArrays PUBLIC ${PROBT3C_INCLUDE_DIRECTORIES})
list(APPEND PROBT3C_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/libBasicArrays.a)
set(PROBT3C_LIBRARIES ${PROBT3C_LIBRARIES} PARENT_SCOPE)
