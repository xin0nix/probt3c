include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit_tests unit_tests.cc)
target_link_libraries(unit_tests gtest gtest_main gmock probt3c_impl)
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR})
include(GoogleTest)
gtest_discover_tests(unit_tests)
