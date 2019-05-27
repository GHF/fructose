add_library(base OBJECT)
target_sources(base
  PRIVATE
    assert.cc
    integer.cc
  PUBLIC
    assert.h
    integer.h
    macros.h
    range_map.h
)
target_link_libraries(fructose
  PUBLIC
    base
)

target_sources(fructose-unittest
  PRIVATE
    assert_unittest.cc
    integer_unittest.cc
    range_map_unittest.cc
)
