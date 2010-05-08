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
