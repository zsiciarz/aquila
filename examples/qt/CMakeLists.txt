################################################################################
#
# GUI examples using Qt toolkit
#
################################################################################

add_subdirectory(qt_wave_properties)
if(QWT_FOUND)
    include_directories(${QWT_INCLUDE_DIRS})
    add_subdirectory(qwt_wave_plot)
    add_subdirectory(qwt_spectrogram)
endif()
