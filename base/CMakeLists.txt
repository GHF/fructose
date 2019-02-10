add_library(base OBJECT)
target_sources(base
  PRIVATE
    integer.cc
  PUBLIC
    integer.h
)
target_link_libraries(fructose
  PUBLIC
    base
)

target_sources(fructose-unittest
  PRIVATE
    integer_unittest.cc
)
