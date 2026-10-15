add_library(lang STATIC)
target_sources(lang
  PRIVATE
    manager.cc
    lua.cc)
target_include_directories(lang
  PUBLIC
    ${CMAKE_SOURCE_DIR}
  PRIVATE
    ${LUA_INCLUDE_DIR})
target_link_libraries(lang
  PUBLIC
    Seastar::seastar
    xxHash::xxhash
  PRIVATE
    absl::headers
    ${LUA_LIBRARIES})

check_headers(check-headers lang
  GLOB_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/*.hh)
