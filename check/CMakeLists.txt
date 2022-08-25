include(FetchContent)
FetchContent_Declare(
  rapidcheck
  GIT_REPOSITORY https://github.com/emil-e/rapidcheck
  GIT_TAG        master
)
FetchContent_MakeAvailable(rapidcheck)

add_executable(basic_vectors_check basic_vectors_check.cc)
target_link_libraries(basic_vectors_check probt3c_impl gtest rapidcheck)
target_include_directories(basic_vectors_check PRIVATE 
  ${CMAKE_SOURCE_DIR} 
  ${rapidcheck_SOURCE_DIR}/extras/gtest/include/
)

# TODO: make cmake routine for this
add_executable(basic_lists_check basic_lists_check.cc)
target_link_libraries(basic_lists_check probt3c_impl gtest rapidcheck)
target_include_directories(basic_lists_check PRIVATE 
  ${CMAKE_SOURCE_DIR} 
  ${rapidcheck_SOURCE_DIR}/extras/gtest/include/
)

add_executable(basic_strings_check basic_strings_check.cc)
target_link_libraries(basic_strings_check probt3c_impl gtest rapidcheck)
target_include_directories(basic_strings_check PRIVATE 
  ${CMAKE_SOURCE_DIR} 
  ${rapidcheck_SOURCE_DIR}/extras/gtest/include/
)

add_executable(basic_graphs_check basic_graphs_check.cc)
target_link_libraries(basic_graphs_check probt3c_impl gtest rapidcheck)
target_include_directories(basic_graphs_check PRIVATE 
  ${CMAKE_SOURCE_DIR} 
  ${rapidcheck_SOURCE_DIR}/extras/gtest/include/
)

