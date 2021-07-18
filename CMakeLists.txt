cmake_minimum_required (VERSION 3.0)

project (ws-chess)

function(create_library lib_name)
  set(library_name ${lib_name}) 

  file(GLOB src_files
      "*.cpp"
  )

  add_library(
    ${library_name}
    ${src_files}
    )

  target_include_directories(${library_name} INTERFACE ${CMAKE_SOURCE_DIR})
endfunction()


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

add_subdirectory("libs/simple-web-sockets")
add_subdirectory("libs/json")
add_subdirectory("libs/googletest")
add_subdirectory("level_up")
add_subdirectory("server")
add_subdirectory("test")
add_subdirectory("main")
