set(qwt_spectrogram_SOURCES
    qwt_spectrogram.cpp
)

add_executable(qwt_spectrogram WIN32 EXCLUDE_FROM_ALL
               ${qwt_spectrogram_SOURCES})
add_dependencies(examples qwt_spectrogram)
target_link_libraries(qwt_spectrogram Aquila Qt5::Widgets ${QWT_LIBRARIES})
