################################################################################
#
# Unit tests for ArrayData class.
#
################################################################################

# iteration
aquila_test(iteration)

add_test(iteration_run iteration)
set_tests_properties(iteration_run
    PROPERTIES PASS_REGULAR_EXPRESSION "024681012141618")
