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


################################################################################
#
# Aquila sources
#
################################################################################

# library headers
set (Aquila_HEADERS
    src/global.h
    src/Exceptions.h
    src/source/SignalSource.h
    src/source/Frame.h
    src/source/WaveFile.h
    src/transform/Window.h
)

# library sources
set (Aquila_SOURCES
    src/source/SignalSource.cpp
    src/source/Frame.cpp
    src/source/WaveFile.cpp
    src/transform/Window.cpp
)


################################################################################
#
# Building and linking
#
################################################################################

# main Aquila library
add_library(Aquila ${Aquila_HEADERS} ${Aquila_SOURCES})

# examples
if(Aquila_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(Aquila_BUILD_EXAMPLES)

#tests
if(Aquila_BUILD_TESTS)
    enable_testing()
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
