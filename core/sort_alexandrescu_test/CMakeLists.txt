project(sort_alexandrescu_test)

add_executable(${PROJECT_NAME} sort_test.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        gtest_main
        sort_alexandrescu
)

# add executable to ctest suit
add_test(${PROJECT_NAME} ${PROJECT_NAME})