################################################################################
#
# Unit tests for WaveFile class.
#
################################################################################


# bits per sample
add_executable(bits_per_sample bits_per_sample.cpp)
target_link_libraries(bits_per_sample Aquila)

add_test(bits_per_sample_run bits_per_sample ${Aquila_TEST_WAVEFILE_8B_MONO})
add_test(bits_per_sample_8b bits_per_sample ${Aquila_TEST_WAVEFILE_8B_MONO})
set_tests_properties(bits_per_sample_8b
    PROPERTIES PASS_REGULAR_EXPRESSION "8")
add_test(bits_per_sample_16b bits_per_sample ${Aquila_TEST_WAVEFILE_16B_MONO})
set_tests_properties(bits_per_sample_16b
    PROPERTIES PASS_REGULAR_EXPRESSION "16")


# number of channels
add_executable(channels channels.cpp)
target_link_libraries(channels Aquila)

add_test(channels_run channels ${Aquila_TEST_WAVEFILE_8B_MONO})
add_test(channels_mono channels ${Aquila_TEST_WAVEFILE_16B_MONO})
set_tests_properties(channels_mono
    PROPERTIES PASS_REGULAR_EXPRESSION "1")
add_test(channels_stereo channels ${Aquila_TEST_WAVEFILE_16B_STEREO})
set_tests_properties(channels_stereo
    PROPERTIES PASS_REGULAR_EXPRESSION "2")


# sample frequency
add_executable(sample_frequency sample_frequency.cpp)
target_link_libraries(sample_frequency Aquila)

add_test(sample_frequency_run sample_frequency ${Aquila_TEST_WAVEFILE_8B_MONO})
add_test(sample_frequency_read sample_frequency ${Aquila_TEST_WAVEFILE_8B_MONO})
set_tests_properties(sample_frequency_read
    PROPERTIES PASS_REGULAR_EXPRESSION "44100")
