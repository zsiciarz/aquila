################################################################################
#
# Aquila unit tests.
#
################################################################################

include_directories("${CMAKE_SOURCE_DIR}")

# path to data files used for testing
set(Aquila_TEST_DATA_PATH "${CMAKE_SOURCE_DIR}/tests/data")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/constants.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/constants.h"
)

# UnitTest++
set(Aquila_Test_SOURCES
    main.cpp
    functions.cpp
    filter/MelFilter.cpp
    filter/MelFilterBank.cpp
    ml/Dtw.cpp
    source/Frame.cpp
    source/FramesCollection.cpp
    source/PlainTextFile.cpp
    source/RawPcmFile.cpp
    source/SignalSource.cpp
    source/WaveFile.cpp
    source/generator/SineGenerator.cpp
    source/generator/SquareGenerator.cpp
    source/generator/TriangleGenerator.cpp
    source/window/BarlettWindow.cpp
    source/window/HammingWindow.cpp
    source/window/RectangularWindow.cpp
    transform/AquilaFft.cpp
    transform/Dft.cpp
    transform/Fft.h
    transform/Fft.cpp
    transform/OouraFft.cpp
    transform/Dct.cpp
)

include_directories(${UNITTESTPP_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(aquila_test EXCLUDE_FROM_ALL ${Aquila_Test_SOURCES})
target_link_libraries(aquila_test Aquila UnitTest++)
add_test(Aquila_TEST_SUITE aquila_test)
