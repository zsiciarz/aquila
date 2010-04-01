################################################################################
#
# Unit tests for WaveFile class.
#
################################################################################


# .wav files
set(Aquila_TEST_WAVEFILE_8B_MONO "${Aquila_TEST_DATA_PATH}/8b_mono.wav")
set(Aquila_TEST_WAVEFILE_8B_STEREO "${Aquila_TEST_DATA_PATH}/8b_stereo.wav")
set(Aquila_TEST_WAVEFILE_16B_MONO "${Aquila_TEST_DATA_PATH}/16b_mono.wav")
set(Aquila_TEST_WAVEFILE_16B_STEREO "${Aquila_TEST_DATA_PATH}/16b_stereo.wav")


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


# wave size
add_executable(wave_size wave_size.cpp)
target_link_libraries(wave_size Aquila)

add_test(wave_size_run wave_size ${Aquila_TEST_WAVEFILE_8B_MONO})
add_test(wave_size_8b_mono wave_size ${Aquila_TEST_WAVEFILE_8B_MONO})
set_tests_properties(wave_size_8b_mono
    PROPERTIES PASS_REGULAR_EXPRESSION "4552")

add_test(wave_size_16b_stereo wave_size ${Aquila_TEST_WAVEFILE_16B_STEREO})
set_tests_properties(wave_size_16b_stereo
    PROPERTIES PASS_REGULAR_EXPRESSION "18208")


# samples count
add_executable(samples_count samples_count.cpp)
target_link_libraries(samples_count Aquila)

add_test(samples_count_run samples_count ${Aquila_TEST_WAVEFILE_8B_MONO})
add_test(samples_count_8b_mono samples_count ${Aquila_TEST_WAVEFILE_8B_MONO})
set_tests_properties(samples_count_8b_mono
    PROPERTIES PASS_REGULAR_EXPRESSION "4552")

add_test(samples_count_16b_stereo samples_count ${Aquila_TEST_WAVEFILE_16B_STEREO})
set_tests_properties(samples_count_16b_stereo
    PROPERTIES PASS_REGULAR_EXPRESSION "4552")
