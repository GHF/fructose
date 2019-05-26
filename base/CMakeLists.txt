add_library(base OBJECT)
target_sources(base
  PRIVATE
    integer.cc
  PUBLIC
    integer.h
    range_map.h
)
target_link_libraries(fructose
  PUBLIC
    base
)

target_sources(fructose-unittest
  PRIVATE
    integer_unittest.cc
    range_map_unittest.cc
)
