project(job_runner)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    # PRIVATE
        sort_alexandrescu
        vt100
)