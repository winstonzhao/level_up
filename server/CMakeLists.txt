cmake_minimum_required (VERSION 3.0)
create_library(server)

target_link_libraries(server simple-websocket-server)
target_link_libraries(server nlohmann_json)
