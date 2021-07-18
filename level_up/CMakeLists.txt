cmake_minimum_required (VERSION 3.0)

add_library(
  level_up
  level_up.cpp
  )

target_include_directories(level_up INTERFACE ${CMAKE_SOURCE_DIR})