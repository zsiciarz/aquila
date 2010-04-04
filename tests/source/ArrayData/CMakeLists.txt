################################################################################
#
# Unit tests for ArrayData class.
#
################################################################################

# iteration
add_executable(iteration iteration.cpp)
target_link_libraries(iteration Aquila)

add_test(iteration_run iteration)
set_tests_properties(iteration_run
    PROPERTIES PASS_REGULAR_EXPRESSION "024681012141618")
