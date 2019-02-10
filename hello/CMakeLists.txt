target_sources(MyLibrary
  PRIVATE
    hello.cc
  PUBLIC
    hello.h
)

target_sources(MyTest
  PRIVATE
    hello_unittest.cc
)

add_executable(hello_cmake)
target_link_libraries(hello_cmake
  PRIVATE
    MyProject::MyLibrary
)
add_sanitizers(hello_cmake)

target_sources(hello_cmake
  PRIVATE
    main.cc
)
