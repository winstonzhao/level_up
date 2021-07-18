cmake_minimum_required (VERSION 3.0)

add_library(
  server
  server.cpp
  )

target_link_libraries(server simple-websocket-server)
target_link_libraries(server nlohmann_json)

target_include_directories(server INTERFACE ${CMAKE_SOURCE_DIR})