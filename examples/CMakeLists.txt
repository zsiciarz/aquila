################################################################################
#
# Example programs using Aquila
#
################################################################################

# all examples use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")

add_subdirectory(frame_iteration)

add_subdirectory(wave_info)
add_subdirectory(wave_iteration)
add_subdirectory(window_data)
add_subdirectory(window_plot)
