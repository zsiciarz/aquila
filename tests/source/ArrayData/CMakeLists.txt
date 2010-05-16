################################################################################
#
# Unit tests for ArrayData class.
#
################################################################################

# sample frequency
aquila_test(ad_sample_frequency)
add_test(ad_sample_frequency_run ad_sample_frequency)
set_tests_properties(ad_sample_frequency_run
    PROPERTIES PASS_REGULAR_EXPRESSION "22050")

# bits per sample
aquila_test(ad_bits_per_sample)
add_test(ad_bits_per_sample_run ad_bits_per_sample)
set_tests_properties(ad_bits_per_sample_run
    PROPERTIES PASS_REGULAR_EXPRESSION "8 16 32 64")

# iteration
aquila_test(iteration)

add_test(iteration_run iteration)
set_tests_properties(iteration_run
    PROPERTIES PASS_REGULAR_EXPRESSION "024681012141618")
