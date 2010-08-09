################################################################################
#
# Unit tests for Frame class.
#
################################################################################

# sample frequency
aquila_test(frame_sample_frequency)
add_test(frame_sample_frequency_run frame_sample_frequency)
set_tests_properties(frame_sample_frequency_run
    PROPERTIES PASS_REGULAR_EXPRESSION "22050")


# bits per sample
aquila_test(frame_bits_per_sample)
add_test(frame_bits_per_sample_run frame_bits_per_sample)
set_tests_properties(frame_bits_per_sample_run
    PROPERTIES PASS_REGULAR_EXPRESSION "1")


# samples count
aquila_test(frame_samples_count)
add_test(frame_samples_count1 frame_samples_count 0 1)
set_tests_properties(frame_samples_count1
    PROPERTIES PASS_REGULAR_EXPRESSION "1")

add_test(frame_samples_count2 frame_samples_count 0 4)
set_tests_properties(frame_samples_count2
    PROPERTIES PASS_REGULAR_EXPRESSION "4")

add_test(frame_samples_count3 frame_samples_count 0 10)
set_tests_properties(frame_samples_count3
    PROPERTIES PASS_REGULAR_EXPRESSION "10")

# clipping
add_test(frame_samples_count4 frame_samples_count 0 15)
set_tests_properties(frame_samples_count4
    PROPERTIES PASS_REGULAR_EXPRESSION "10")

add_test(frame_samples_count5 frame_samples_count 9 20)
set_tests_properties(frame_samples_count5
    PROPERTIES PASS_REGULAR_EXPRESSION "1")


# per-sample access
aquila_test(frame_sample)
add_test(frame_sample1 frame_sample 0 10 0)
set_tests_properties(frame_sample1
    PROPERTIES PASS_REGULAR_EXPRESSION "0")

add_test(frame_sample2 frame_sample 1 10 0)
set_tests_properties(frame_sample2
    PROPERTIES PASS_REGULAR_EXPRESSION "1")

add_test(frame_sample3 frame_sample 2 10 2)
set_tests_properties(frame_sample3
    PROPERTIES PASS_REGULAR_EXPRESSION "4")

add_test(frame_sample4 frame_sample 9 10 0)
set_tests_properties(frame_sample4
    PROPERTIES PASS_REGULAR_EXPRESSION "9")

add_test(frame_sample5 frame_sample 6 7 1)
set_tests_properties(frame_sample5
    PROPERTIES PASS_REGULAR_EXPRESSION "7")
