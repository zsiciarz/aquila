################################################################################
#
# Example programs using Aquila
#
################################################################################

# all examples use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")


# a common setup for most of the examples
macro(aquila_example example)
  add_executable(${example} EXCLUDE_FROM_ALL ${example}.cpp)
  add_dependencies(examples ${example})
  target_link_libraries(${example} Aquila)
endmacro(aquila_example)


add_subdirectory(utility_functions)

add_subdirectory(frame_iteration)

add_subdirectory(wave_info)
add_subdirectory(wave_iteration)
add_subdirectory(window_data)
add_subdirectory(window_plot)

add_subdirectory(text_plot)

add_subdirectory(sine_generator)
add_subdirectory(square_generator)
add_subdirectory(generators)

add_subdirectory(fft_comparison)
add_subdirectory(fft_simple_spectrum)
add_subdirectory(fft_filter)
