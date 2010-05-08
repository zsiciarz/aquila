################################################################################
#
# Unit tests for Fft and derived classes.
#
################################################################################


# .wav files

# Find the sine wave frequency
aquila_test(sine_peak_detect)

add_test(sine_peak_detect_1 sine_peak_detect 64 8000 1000)
set_tests_properties(sine_peak_detect_1
    PROPERTIES PASS_REGULAR_EXPRESSION "8")

add_test(sine_peak_detect_2 sine_peak_detect 64 8000 2000)
set_tests_properties(sine_peak_detect_2
    PROPERTIES PASS_REGULAR_EXPRESSION "16")

add_test(sine_peak_detect_3 sine_peak_detect 64 8000 3999)
set_tests_properties(sine_peak_detect_3
    PROPERTIES PASS_REGULAR_EXPRESSION "31")

add_test(sine_peak_detect_4 sine_peak_detect 64 8000 1)
set_tests_properties(sine_peak_detect_4
    PROPERTIES PASS_REGULAR_EXPRESSION "0")

add_test(sine_peak_detect_5 sine_peak_detect 1024 8000 1000)
set_tests_properties(sine_peak_detect_5
    PROPERTIES PASS_REGULAR_EXPRESSION "128")

add_test(sine_peak_detect_6 sine_peak_detect 1024 8000 2000)
set_tests_properties(sine_peak_detect_6
    PROPERTIES PASS_REGULAR_EXPRESSION "256")

add_test(sine_peak_detect_7 sine_peak_detect 1024 44100 1000)
set_tests_properties(sine_peak_detect_7
    PROPERTIES PASS_REGULAR_EXPRESSION "23")

add_test(sine_peak_detect_8 sine_peak_detect 1024 44100 2000)
set_tests_properties(sine_peak_detect_8
    PROPERTIES PASS_REGULAR_EXPRESSION "46")

add_test(sine_peak_detect_9 sine_peak_detect 1024 44100 4567)
set_tests_properties(sine_peak_detect_9
    PROPERTIES PASS_REGULAR_EXPRESSION "106")

add_test(sine_peak_detect_10 sine_peak_detect 1024 44100 10000)
set_tests_properties(sine_peak_detect_10
    PROPERTIES PASS_REGULAR_EXPRESSION "232")

add_test(sine_peak_detect_11 sine_peak_detect 1024 44100 15000)
set_tests_properties(sine_peak_detect_11
    PROPERTIES PASS_REGULAR_EXPRESSION "348")

add_test(sine_peak_detect_12 sine_peak_detect 1024 44100 21204)
set_tests_properties(sine_peak_detect_12
    PROPERTIES PASS_REGULAR_EXPRESSION "492")
