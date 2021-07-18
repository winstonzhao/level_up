enable_testing()

add_executable(
  test
  test.cc
)
target_link_libraries(test gtest_main)
target_link_libraries(test level_up)

include(GoogleTest)
gtest_discover_tests(test)