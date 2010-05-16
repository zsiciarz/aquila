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
