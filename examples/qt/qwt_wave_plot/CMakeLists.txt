set(qwt_wave_plot_SOURCES
    qwt_wave_plot.cpp
)

add_executable(qwt_wave_plot WIN32 EXCLUDE_FROM_ALL
               ${qwt_wave_plot_SOURCES})
add_dependencies(examples qwt_wave_plot)
target_link_libraries(qwt_wave_plot Aquila Qt5::Widgets ${QWT_LIBRARIES})
