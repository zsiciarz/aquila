cmake_minimum_required(VERSION 2.6)
project(Aquila CXX)

set(Aquila_VERSION_MAJOR 3)
set(Aquila_VERSION_MINOR 0)
set(Aquila_VERSION_PATCH 0)


################################################################################
#
# Build options
#
################################################################################

set(Aquila_BUILD_EXAMPLES ON CACHE BOOL "Build example programs?" FORCE)
set(Aquila_BUILD_TESTS ON CACHE BOOL "Build test programs?" FORCE)


################################################################################
#
# Dependencies
#
################################################################################

# Boost 
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# libraries bundled with Aquila
add_subdirectory(lib)

################################################################################
#
# Aquila sources
#
################################################################################

# library headers
set (Aquila_HEADERS
    src/global.h
    src/functions.h
    src/Exceptions.h
    src/source/SignalSource.h
    src/source/Frame.h
    src/source/FramesCollection.h
    src/source/ArrayData.h
    src/source/WaveFile.h
    src/source/generator/Generator.h
    src/source/generator/SineGenerator.h
    src/transform/Fft.h
    src/transform/AquilaFft.h
    src/transform/OouraFft.h
    src/transform/Window.h
    src/tools/TextPlot.h
)

# library sources
set (Aquila_SOURCES
    src/source/SignalSource.cpp
    src/source/Frame.cpp
    src/source/FramesCollection.cpp
    src/source/WaveFile.cpp
    src/source/generator/Generator.cpp
    src/source/generator/SineGenerator.cpp
    src/transform/AquilaFft.cpp
    src/transform/OouraFft.cpp
    src/transform/Window.cpp
    src/tools/TextPlot.cpp
)


################################################################################
#
# Compiler-specific workarounds
#
################################################################################

if(MSVC)
    # disable "strncpy is deprecated" warning and enable math constants
    add_definitions("/D_CRT_NONSTDC_NO_DEPRECATE /D_USE_MATH_DEFINES")
endif(MSVC)


################################################################################
#
# Building and linking
#
################################################################################

# main Aquila library
add_library(Aquila ${Aquila_HEADERS} ${Aquila_SOURCES})

# linking with extra libs
target_link_libraries(Aquila Ooura_fft)

# examples
if(Aquila_BUILD_EXAMPLES)
    add_custom_target(examples)
    add_subdirectory(examples)
endif(Aquila_BUILD_EXAMPLES)

#tests
if(Aquila_BUILD_TESTS)
    enable_testing()
    add_custom_target(tests)
    add_subdirectory(tests)
endif(Aquila_BUILD_TESTS)


################################################################################
#
# Installing
#
################################################################################

# install the binaries and include files
install(TARGETS Aquila ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/aquila FILES_MATCHING PATTERN "*.h")
install(FILES CHANGELOG LICENSE README DESTINATION ${CMAKE_INSTALL_PREFIX})


################################################################################
#
# Uninstalling
#
################################################################################

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake")
