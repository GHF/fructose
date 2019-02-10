add_library(catch2-main OBJECT)
add_library(Fructose::catch2-main ALIAS catch2-main)
target_link_libraries(catch2-main
  PRIVATE
    Catch2::Catch2
)
target_sources(catch2-main
  PRIVATE
    catch2_main.cc
)
