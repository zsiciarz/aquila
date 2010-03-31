################################################################################
#
# Aquila unit tests.
#
################################################################################

# all tests use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")

# path to data files used for testing
set(Aquila_TEST_DATA_PATH "${CMAKE_SOURCE_DIR}/tests/data")

add_subdirectory(source)
