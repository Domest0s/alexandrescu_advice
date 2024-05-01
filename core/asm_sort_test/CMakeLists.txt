project(asm_sort_test)

set(SOURCE_FILES
  test_bubble_sort.cpp
  test_quick_asm_sort.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    asm_sort
    GTest::GTest
    rnum_generator
)

# register executable to the CTest suite
add_test(asm_sort_testing asm_sort_test)
