################################################################################
#
# Unit tests for ArrayData class.
#
################################################################################

# iteration
add_executable(iteration iteration.cpp)
target_link_libraries(iteration Aquila)

add_test(iteration_run iteration)
