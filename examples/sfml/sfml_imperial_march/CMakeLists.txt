
add_executable(sfml_imperial_march EXCLUDE_FROM_ALL sfml_imperial_march.cpp)
add_dependencies(examples sfml_imperial_march)
target_link_libraries(sfml_imperial_march Aquila ${SFML_LIBRARY})
