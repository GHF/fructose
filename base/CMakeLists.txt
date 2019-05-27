target_sources(fructose
  PRIVATE
    assert.cc
  PUBLIC
    assert.h
    integer.h
    macros.h
    range_map.h
)

target_sources(fructose-unittest
  PRIVATE
    assert_unittest.cc
    integer_unittest.cc
    range_map_unittest.cc
)
