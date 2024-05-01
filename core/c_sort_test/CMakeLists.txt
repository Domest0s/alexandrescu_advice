project(c_sort_test CXX)

include(GoogleTest)

add_executable(${PROJECT_NAME}
  bubble_test.cpp
  insertion_test.cpp
  selection_test.cpp
  qsort_test.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    GTest::gtest_main
    rnum_generator
    c_sort
)

gtest_discover_tests(${PROJECT_NAME})

# Add a test to the project to be run by ctest
#add_test(NAME c_sort_testing
 # COMMAND ${PROJECT_NAME}
#)
