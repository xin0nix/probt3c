include(FetchContent)
FetchContent_Declare(
  rapidcheck
  GIT_REPOSITORY https://github.com/emil-e/rapidcheck
  GIT_TAG        master
)
FetchContent_MakeAvailable(rapidcheck)

add_executable(check check.cc)
target_link_libraries(check
  probt3c_impl
  gtest
  rapidcheck
)
target_include_directories(check PRIVATE 
  ${CMAKE_SOURCE_DIR} 
  ${rapidcheck_SOURCE_DIR}/extras/gtest/include/
)
