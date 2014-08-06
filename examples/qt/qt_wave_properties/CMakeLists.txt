set(qt_wave_properties_SOURCES
    WavePropertiesWidget.cpp
    MainWindow.cpp
    qt_wave_properties.cpp
)
set(qt_wave_properties_MOC_HEADERS
    WavePropertiesWidget.h
    MainWindow.h
)
set(qt_wave_properties_UIS
    MainWindow.ui
)
qt5_wrap_ui(qt_wave_properties_UI_SOURCES ${qt_wave_properties_UIS})

add_executable(qt_wave_properties WIN32 EXCLUDE_FROM_ALL
               ${qt_wave_properties_SOURCES}
               ${qt_wave_properties_MOC_SOURCES}
               ${qt_wave_properties_UI_SOURCES})
add_dependencies(examples qt_wave_properties)
target_link_libraries(qt_wave_properties Aquila Qt5::Widgets)
