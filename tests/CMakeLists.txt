################################################################################
#
# Aquila unit tests.
#
################################################################################

# all tests use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")

# path to data files used for testing
set(Aquila_TEST_DATA_PATH "${CMAKE_SOURCE_DIR}/tests/data")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/constants.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/constants.h"
)

# UnitTest++
set(Aquila_Test_SOURCES
    main.cpp
    source/ArrayData.cpp
    source/Frame.cpp
    source/PlainTextFile.cpp
    source/RawPcmFile.cpp
    source/WaveFile.cpp
    source/generator/SquareGenerator.cpp
    transform/Fft.cpp
)

include_directories(${UNITTESTPP_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(aquila_test EXCLUDE_FROM_ALL ${Aquila_Test_SOURCES})
target_link_libraries(aquila_test Aquila UnitTest++)
add_test(Aquila_TEST_SUITE aquila_test)
