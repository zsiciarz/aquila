################################################################################
#
# Aquila unit tests.
#
################################################################################

# all tests use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")


# a common setup for most of the tests
macro(aquila_test test)
  add_executable(${test} EXCLUDE_FROM_ALL ${test}.cpp)
  add_dependencies(tests ${test})
  target_link_libraries(${test} Aquila)
endmacro(aquila_test)


# path to data files used for testing
set(Aquila_TEST_DATA_PATH "${CMAKE_SOURCE_DIR}/tests/data")

add_subdirectory(source)
