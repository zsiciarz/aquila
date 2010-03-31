################################################################################
#
# Aquila unit tests.
#
################################################################################

# all tests use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")

# list some files used for testing
set(Aquila_TEST_DATA_PATH "${CMAKE_SOURCE_DIR}/tests/data")
set(Aquila_TEST_WAVEFILE_8B_MONO "${Aquila_TEST_DATA_PATH}/8b_mono.wav")
set(Aquila_TEST_WAVEFILE_8B_STEREO "${Aquila_TEST_DATA_PATH}/8b_stereo.wav")
set(Aquila_TEST_WAVEFILE_16B_MONO "${Aquila_TEST_DATA_PATH}/16b_mono.wav")
set(Aquila_TEST_WAVEFILE_16B_STEREO "${Aquila_TEST_DATA_PATH}/16b_stereo.wav")

add_subdirectory(source)
