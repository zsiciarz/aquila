################################################################################
#
# Example programs using Aquila
#
################################################################################

include_directories("${CMAKE_SOURCE_DIR}")


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
add_subdirectory(window_plot)
add_subdirectory(window_usage)

add_subdirectory(text_plot)

add_subdirectory(sine_generator)
add_subdirectory(square_generator)
add_subdirectory(triangle_generator)
add_subdirectory(generators)

add_subdirectory(am_modulation)

add_subdirectory(fft_comparison)
add_subdirectory(fft_simple_spectrum)
add_subdirectory(fft_filter)
add_subdirectory(spectrogram)
add_subdirectory(mfcc_calculation)
add_subdirectory(dtw_path_recovery)

# Qt-based examples will be built only when Qt itself can be located
if(NOT MSVC)
    find_package(Qt5Widgets)
    if(Qt5Widgets_FOUND)
        message("Qt5 was found, GUI examples using Qt will be built.")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
        set(CMAKE_AUTOMOC ON)
        find_package(Qwt)
        add_subdirectory(qt)
        if(QWT_FOUND)
            message("Additionally, Qwt widget examples will be built.")
        endif()
    else()
        message("Qt5 was not found, no GUI examples using Qt will be built.")
    endif()
endif()

if(SFML_FOUND)
    add_subdirectory(sfml)
endif()
