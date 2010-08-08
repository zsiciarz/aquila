################################################################################
#
# Unit tests for SquareGenerator class.
#
################################################################################

# duty cycle
aquila_test(sg_duty_cycle)
add_test(sg_duty_cycle_run sg_duty_cycle)
set_tests_properties(sg_duty_cycle_run
    PROPERTIES PASS_REGULAR_EXPRESSION "^500")

add_test(sg_duty_cycle_25 sg_duty_cycle 0.25)
set_tests_properties(sg_duty_cycle_25
    PROPERTIES PASS_REGULAR_EXPRESSION "^250")

add_test(sg_duty_cycle_75 sg_duty_cycle 0.75)
set_tests_properties(sg_duty_cycle_75
    PROPERTIES PASS_REGULAR_EXPRESSION "^750")

add_test(sg_duty_cycle_0 sg_duty_cycle 0.0)
set_tests_properties(sg_duty_cycle_0
    PROPERTIES PASS_REGULAR_EXPRESSION "^0")

add_test(sg_duty_cycle_1 sg_duty_cycle 1.0)
set_tests_properties(sg_duty_cycle_1
    PROPERTIES PASS_REGULAR_EXPRESSION "^1000")

add_test(sg_duty_cycle_001 sg_duty_cycle 0.01)
set_tests_properties(sg_duty_cycle_001
    PROPERTIES PASS_REGULAR_EXPRESSION "^10")
