enable_testing()

file(GLOB src_files
      "*.cpp"
  )

add_executable(
  test
  ${src_files}
)

target_link_libraries(test gtest_main)
target_link_libraries(test gmock_main)
target_link_libraries(test level_up)

include(GoogleTest)
gtest_discover_tests(test)