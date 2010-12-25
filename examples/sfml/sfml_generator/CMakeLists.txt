
add_executable(sfml_generator sfml_generator.cpp)
add_dependencies(examples sfml_generator)
target_link_libraries(sfml_generator Aquila ${SFML_LIBRARY})
